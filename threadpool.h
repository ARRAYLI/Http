/*************************************************************************
	> File Name: threadpool.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 16时27分54秒
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>

/*
 * 线程池里的所有的运行和等待的任务都是一个 CThread_worker
 * 由于所有任务都在链表里，所以是一个链表结构
 * */

/* 链表结点结构体 */
typedef struct worker
{
    /* 回调函数，任务运行时会执行此函数，注意也可以声明成其他方式 */ 
    void* (*process)(void *arg);
    void* arg;  /* 回调函数的参数 */
    struct worker* next;
}CThread_worker;

/* 线程池结构体 */
typedef struct
{
    /* 互斥锁 */
    pthread_mutex_t queue_lock;   
    /* 条件变量 */
    pthread_cond_t queue_ready;

    /* 链表结构，线程池中所有等待任务 */
    CThread_worker *queue_head;
    /* 是否销毁线程池 */
    int shutdown;
    pthread_t* threadId;

    /* 线程中允许活动的数目 */
    int max_thread_num;
    /* 当前等待任务队列的数目 */
    int cur_queue_size;
}threadpool_t;

/* 创建线程池 */
threadpool_t *threadpool_create(int max_thr_num);
    
/* 向线程池中添加任务 */
int threadpool_add_task(threadpool_t* pool,void* (*process)(void*arg),void* arg);

/* 销毁线程池 
 * 等待队列中的任务不会再执行，但是正在运行的线程会一直把任务运行完后退出 */
int destroy_threadpool(threadpool_t *pool);

/* 线程处理函数 */
void *thread_routine(void *arg);
#endif
