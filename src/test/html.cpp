/*************************************************************************
	> File Name: html.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月11日 星期一 17时32分11秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main(void)
{
    char buf[] = {"aaaaaaaaaaaaaa \r\n"};
    int len = strlen(buf);
    char str[1024];
    int i = 0;
    int j = 0;
    int res = strcmp("\n",buf); 
    printf("res = %d\nstr = %s\n",res,str);
    return 0;
}
