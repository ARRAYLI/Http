/*************************************************************************
    > File Name: http.h
    > Author: 
    > Mail: 
    > Created Time: 2018年06月10日 星期日 19时47分10秒
 ************************************************************************/

#ifndef _HTTP_H
#define _HTTP_H

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<string.h>
#include<sys/sendfile.h>
#include<strings.h>
#include<ctype.h>
#include<sys/wait.h>

/* 最大连接数 */
#define LISTEN_NUM 10

/* 缓冲区大小 */
#define BUFSIZE 1024

/* 错误退出码 
 * ERROR_USE        使用错误
 * ERROR_SOCKET     socket() 创建失败
 * ERROR_BIND       bind()  函数绑定失败
 * ERROR_LISTEN     listen() 函数失败
 * ERROR_EXECL      execl() 程序替换失败
 * */
 enum STATS
 {
     ERROR_USE,
     ERROR_SOCKET,
     ERROR_BIND,
     ERROR_LISTEN,
     ERROR_EXECL
 };
 
/*
 * 函数名称：   http_start_up()
 * 函数功能：   创建一个 socket 监听套接字
 * 参数：       
 *    ip  :     指定服务器的 IP 地址
 *    port:     要绑定套接字的端口
 */
int http_start_up(const char*ip,int port);

/*
 * 函数名称：  http_handler_request()
 * 函数功能：  线程执行函数，负责浏览器发来的请求，分析发送静态网页还是 CGI 脚本
 */
void* http_handler_request(void *newfd);

/*
 * 函数名称：   http_handler_request()
 * 函数功能：   从 socket 中读取一行 http 报文
 * 函数参数：
 *      sockfd :  要读的 socket 文件描述符
 *      buff   :  读到缓冲区的大小
 *      length :  缓冲区的长度
 */
int http_getline(int sockfd,char*buf,int length);

/*
 * 函数名称： http_execute_cgi()
 * 函数功能： 创建子进程，并进行程序替换，执行 cgi 脚本
 * 参数：
 *      sockfd :  与客户端连接的 socket 描述
 *      method :  客户端发来的请求方法
 *      path   :  可执行 cgi 脚本的路径
 *      query_string: GET  方法的参数指针
 */
int http_execute_cgi(int sockfd,const char*method,const char*path,const char* query_string);

/*
 * 函数名称：  http_send_html()
 * 函数功能：  发送本地 html 给客户端
 * 参数:
 *      sockfd :  与客户端连接的 socket 文件描述符
 *      path   :  html 文档的路径
 *      file_size: html 文档的大小
 */
int http_send_html(int sockfd,const char* path,int file_size);

/*
 * 函数名称：http_clear_head()
 * 函数功能：读取并丢弃 http 报文请求剩余的部分
 */

int http_clear_head(int sockfd);

/* 三个错误反馈函数 */
 
/*
* 服务器拒绝访问
*/
int http_echo_404(int sockfd);

/*
 * 没有找到请求资源
 */
int http_echo_403(int sockfd);

/*
 * 尚未实施：服务器不具完备请求的功能
 */
int http_echo_501(int sockfd);

/* 
 * 根据 state 向客户端发送错误反馈
 */
int http_echo_error(int sockfd,int state);

#endif
