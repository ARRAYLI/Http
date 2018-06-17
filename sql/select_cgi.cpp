/*************************************************************************
	> File Name: select.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 10时51分30秒
 ************************************************************************/

#include"sql.h"
#include<unistd.h>
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void send_200()
{
    string stat = "HTTP/1.0 200 OK\r\n";
    cout<<stat;
    //string type = "ContentType: /text/html\r\n";
    string type = "ContentType: text/html\r\n";
    cout<<type;
    string blank = "\r\n";
    cout<<blank;
}

void send_404()
{
    string stat = "HTTP/1.0 404 NOT FOUND\r\n";
    cout<<stat;
    //string type = "ContentType: /text/html\r\n";
    string type = "ContentType: text/html\r\n";
    cout<<type;
    string blank = "\r\n";
    cout<<blank;
}

bool get_arg(char* buf)
{
    char* method = NULL;
    char* arg_string = NULL;
    char* content_length = NULL;
    
    method = getenv("METHOD");
   
    /* 从环境变量 获取到 method ，如果是 GET 方法的话，继续获取 QUERY_STRING */
    if(method && strcasecmp(method,"GET") == 0)
    {
        arg_string = getenv("QUERY_STRING");
        if(!arg_string)
            return false;
        strcpy(buf,arg_string);
    }
    else if(method && strcasecmp(method,"POST") == 0)
    {
        content_length = getenv("CONTENT_LENGTH");   
        if(!content_length)
        {
           return false; 
        }
        int i = 0;
        char c = '\0';
        int nums = atoi(content_length);
        for( ; i<nums; i++ )
        {
           read(STDIN_FILENO,&c,1); 
            buf[i] = c;
        }
        buf[i] = '\0';
        return true;
    }
    return false;
}

#if 0 
int get_data(char* buf)
{
    assert(buf);
    char* method = NULL;
    char* arg_string = NULL;
    char* content_length = NULL;
    
    method = getenv("METHOD");
   
    /* 从环境变量 获取到 method ，如果是 GET 方法的话，继续获取 QUERY_STRING */
    if(method && strcasecmp(method,"GET") == 0)
    {
        arg_string = getenv("QUERY_STRING");
        if(!arg_string)
        {
            /* cerr 和 cout 的区别：cerr 是标准错误输出，不经过缓冲区直接输出，一般用于迅速输出错误信息，不可以重定向
             * 故只能输出到显示器上
             * cout 是标准输出，输出到显示器上，经过缓冲区，可以被重定向 
             */
            cerr<<"get method GET arg error"<<endl;
            return 1;
        }
        strcpy(buf,arg_string);
    }
    else if(method && strcasecmp(method,"POST") == 0)
    {
        content_length = getenv("CONTENT_LENGTH");   
        if(!content_length)
        {
            cerr<<"get method POST CONTENT_LENGTH error"<<endl;
           return 2;
        }
        int i = 0;
        char c = '\0';
        int nums = atoi(content_length);
        for( ; i<nums; i++ )
        {
           read(STDIN_FILENO,&c,1); 
            buf[i] = c;
        }
        buf[i] = '\0';
        return true;
    }
    else
    {
       cerr<<"get method error" <<endl;
        return 3;
    }
    return 0;
}
#endif

int main(void)
{
    char buf[1024];
    get_arg(buf);
    send_200();
    cout<<"<HTML><H1>ALL USERS</H1><br>"<<endl;
    SqlConnector sql;
    if(sql.connect())
    {
       sql.select(); 
    }
    cout<<" </HTML>";
    return 0;
}
