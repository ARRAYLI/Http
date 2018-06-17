/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 18时55分52秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include"threadpool.h"

void* handler(void* arg)
{
    printf("thread Id is 0x%u,woking task %d\n",(unsigned int)pthread_self(),*(int*)arg);
    sleep(1);
}

int main(void)
{
    threadpool_t * pool = threadpool_create(3);
    
    int*workingnum = (int*)malloc(sizeof(int)*10);

    for(int i=0;i<10;i++)
    {
        workingnum[i] = i;
        threadpool_add_task(pool,handler,&workingnum[i]);        
    }
    
    sleep(5);
    destroy_threadpool(pool);

    free(workingnum);
    workingnum = NULL;
    return 0;
}

