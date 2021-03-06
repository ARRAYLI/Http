/*************************************************************************
	> File Name: threadpool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 17时13分36秒
 ************************************************************************/
#include"threadpool.h"
#include<stdio.h>

/* 创建线程池 */
threadpool_t *threadpool_create(int max_thr_num)
{
    threadpool_t *pool = NULL;
    /* 为线程池动态申请内存，开辟空间 */
    pool = (threadpool_t*)malloc(sizeof(threadpool_t));
    if(pool == NULL)
    {
        printf("threadpool create failed!");
        return NULL;
    }

    /* 初始化互斥量 */
    pthread_mutex_init(&pool->queue_lock,NULL);

    /* 初始化条件变量 */
    pthread_cond_init(&pool->queue_ready,NULL);
    
    /* 初始化任务队列 */
    pool->queue_head = NULL;

    /* 初始化允许线程活动的最大数目 */
    pool->max_thread_num = max_thr_num;

    /* 初始化当前队列的大小 */
    pool->cur_queue_size = 0;

    /* 设置关闭线程池的标志位 */
    pool->shutdown = 0;

    /* 为线程 Id 动态开辟空间 */
    pool->threadId = (pthread_t*) malloc(sizeof(pthread_t) * max_thr_num);
    if( NULL == pool->threadId )
    {
       printf("pool->threadId create failed!\n"); 
       return NULL;
    }

    /* 开始为线程池创建 max_thr_num 个线程 */
    for(int i = 0; i < pool->max_thread_num; i++ )
    {
        pthread_create(&pool->threadId[i],NULL,thread_routine,(void*)pool);    
    }

    /* 返回线程池句柄 */
    return pool;
}
    
/* 向线程池中添加任务 */
int threadpool_add_task(threadpool_t* pool,void* (*process)(void*arg),void* arg)
{
    /* 构造一个新的任务 */
    CThread_worker *newworker = (CThread_worker*)malloc(sizeof(CThread_worker));
    if( NULL == newworker )
    {
       printf("create CThread_worker failed!\n"); 
        return -1;
    }
    newworker->process = process;
    newworker->arg = arg;
    newworker->next = NULL;

    /* 上锁 */
    pthread_mutex_lock(&pool->queue_lock);
    
    /* 将任务放到等待队列中，加入队尾 */
    CThread_worker *member = pool->queue_head;

    if(member != NULL)
    {
        /* 找到队列中的最后一个结点的位置 */

       while(member->next != NULL)
        {
            member = member->next;
        }
        member->next = newworker;
    }
    else
        pool->queue_head = newworker;

    /* 检查一下当前任务队列是否为空 */
    assert(pool->queue_head != NULL);
    pool->cur_queue_size++;

    /* 添加完任务后，解开互斥锁 */
    pthread_mutex_unlock(&pool->queue_lock);
    
    /* 等待队列中有任务来了，唤醒线程池中的一个线程。注意：如果所有的线程都在忙碌的话，那么下面的这句话不起作用，直到有空闲线程 */
    pthread_cond_signal(&pool->queue_ready);

    return 0;
}

/* 销毁线程池 
 * 等待队列中的任务不会再执行，但是正在运行的线程会一直把任务运行完后退出 */
int destroy_threadpool(threadpool_t *pool)
{
    /* 防止两次调用，即已经释放了线程池资源，再次释放避免出错 */
    if( pool->shutdown )
        return -1;
    /* 线程池关闭标志位置为 1 ,表示 关闭线程池，释放资源 */
    pool->shutdown = 1;

    /* 唤醒所有等待线程，线程池要销毁了 */
    pthread_cond_broadcast(&pool->queue_ready);

    /* 阻塞等待线程退出，否则就变成了僵尸进程 */
    for(int i = 0;i < pool->max_thread_num; i++)
    {
        pthread_join(pool->threadId[i],NULL);
    }
    
    /* 释放线程 Id 数组 */
    free(pool->threadId);
    pool->threadId = NULL;
    
    /* 销毁任务队列 */
    CThread_worker * head = NULL;
    while(pool->queue_head!= NULL)
    {
       head = pool->queue_head; 
        pool->queue_head = head->next;
        
        free(head);
        head = NULL;
    }
    /* 销毁条件变量和互斥量*/
    pthread_mutex_destroy(&pool->queue_lock);
    pthread_cond_destroy(&pool->queue_ready);

    /* 销毁线程池句柄 */
    free(pool);
    pool = NULL;
    return 0;
}

/* 线程处理函数 */
void *thread_routine(void *arg)
{
   threadpool_t *pool = (threadpool_t*)arg;
    printf("starting thread 0x%u\n",(unsigned int)pthread_self());

    while(1)
    {
        /* 给线程上锁，进入临界资源区 */
        pthread_mutex_lock(&pool->queue_lock);
        
        /* 如果等待队列为 0 并且不销毁线程池，则线程处于阻塞状态：
         * pthread_cond_wait() 函数是一个原子操作，等待前会解锁，唤醒后会加锁 */

        while( pool->cur_queue_size == 0 && ! pool->shutdown )
        {
            printf("thread 0x%u is waiting\n",(unsigned int)pthread_self());
            pthread_cond_wait(&pool->queue_ready,&pool->queue_lock);
        }

        /* 如果线程池要销毁了，关闭线程池里的每一个线程，自行退出处理 */
        if( pool->shutdown )
        {
           pthread_mutex_unlock(&pool->queue_lock);
           printf("thread 0x%u will exit\n",(unsigned int)pthread_self()); 

            /* 退出当前线程 */
            pthread_exit(NULL);
        }
        
        printf("thread 0x%u start working\n",(unsigned int)pthread_self());
        
        /* 任务队列不为空 
         * 调试信息：判断当前任务队列是否有任务，则继续向下执行程序；否则：程序出错；
         * */
        assert(pool->cur_queue_size != 0);

        /* 调试信息： 如果当前任务队列不存在的话，则出错 */
        assert(pool->queue_head);

        /* 等待任务队列中的任务数减 1，从队列中取出任务 */
        pool->cur_queue_size--;

        CThread_worker *worker = pool->queue_head;
        pool->queue_head  = worker->next;
       
        /* 解锁 */
        pthread_mutex_unlock(&pool->queue_lock);

        /* 调用回调函数 */
        (*(worker->process))(worker->arg);

        /* 释放结点 */
        free(worker);
        worker = NULL;
    }
    /* 这句话不可达 */ 
    pthread_exit(NULL);
}

