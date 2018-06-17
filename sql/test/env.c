/*************************************************************************
	> File Name: env.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 11时06分12秒
 ************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

extern char** environ;
/* 本程序为测试打印出系统的环境变量 */
int main(void)
{
    char *p = getenv("USER");
    printf("\n\np = %s\n",p);
    
    putenv("abcd=test");
    int i;
    for( i = 0;environ[i];i++ )
    {
        printf("%s\n",environ[i]);
    }


    printf("\n\n abcde=%s\n",getenv("abcd"));
    return 0;
}
