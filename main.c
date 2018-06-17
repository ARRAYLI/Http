/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 19时07分27秒
 ************************************************************************/

#include"threadpool.h"
#include"http.h"
#include<signal.h>
#include<string.h>
#include<stdio.h>

#define MAX_THREAD_NUM 5


/* 解析程序参数 */
int getopt_cmd(int argc,char* argv[])
{
    const char *ptr = "ds";
    char ch;

    int dameon_flag = 0;

    while((ch = getopt(argc,argv,ptr)) != -1)
    {
        switch(ch)
        {
            case 'd':
            {
                dameon_flag = 1;
                printf("Http Server 以守护进程方式启动\n");
            }
            break;
            case 's':
            {
                dameon_flag = 0;
                printf("Http Server 以前台方式启动\n");
            }
            break;
            default:
            {
                dameon_flag= 0;
                printf("Http Server 以前台方式启动\n");
            }
            break;
        }

    }
    return dameon_flag;
}


/* 命令行参数错误 */
static void http_usage(const char*proc)
{
    printf("Usage:%s [server_ip] [server_port] [d]\n",proc);    
}

int main(int argc,char* argv[])
{
    /* 当浏览器断开时，忽略 SIGPIPE信号，否则程序异常断开*/
    signal(SIGPIPE,SIG_IGN);
    
    if(argc != 3 && argc != 4)
    {
       http_usage(argv[0]); 
        return ERROR_USE;
    }

    /* 解析命令行参数 */
    int dameon_flag = getopt_cmd(argc,argv); 
    if(dameon_flag)
    {
        daemon(0,0);
    }

    /* 创建线程池 */
    threadpool_t *pool = threadpool_create(MAX_THREAD_NUM);
    
    /* 服务器端创建 socket */
    int listen_fd = http_start_up(argv[1],atoi(argv[2]));

    /* 主进程循环等待客户端的连接请求并处理 */
    while(1)
    {
       struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(struct sockaddr_in);

        int client_fd = accept(listen_fd,(struct sockaddr*)&client_addr,&client_len);
        if(client_fd <0 )
        {
            printf("error: accept()"); 
            continue;
        }
        //printf("client_fd = %d\n OK",client_fd);    
        /* 把刚刚建立好的客户端请求交给线程来处理
        *  从线程池中取出一个线程来执行客户端的请求
        * */
        threadpool_add_task(pool,http_handler_request,(void*)&client_fd);
    }

    return 0;
}

