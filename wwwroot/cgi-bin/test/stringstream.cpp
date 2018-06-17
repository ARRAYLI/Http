/*************************************************************************
	> File Name: stringstream.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月15日 星期五 09时23分36秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int main(void)
{
    stringstream stream;
    string result;
    int i = 1000;
    stream << i;
    stream >> result;
    cout<<result<<endl;

    return 0;
}

