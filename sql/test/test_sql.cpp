/*************************************************************************
	> File Name: test_sql.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 10时03分46秒
 ************************************************************************/

#include"sql.h"
#include<iostream>
using namespace std;

int main(void)
{
    SqlConnector sql;
    sql.connect();
    sql.select();

    return 0;
}

