/*************************************************************************
	> File Name: getopt.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 20时09分47秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
    
    char *ptr = "ds";
    char ch;

    while((ch = getopt(argc,argv,ptr)) != -1)
    {
       switch(ch)
        {
            case 'd':
            printf("daemon start\n");
            break;
            case 's':
            printf("server running\n");
            break;
            default:
            printf("default\n");
            break;
        }

    }

    return 0;
}
