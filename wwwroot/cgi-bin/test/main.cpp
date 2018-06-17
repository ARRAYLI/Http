/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月14日 星期四 19时24分35秒
 ************************************************************************/

#include"Calc.h"
#include<string>
#include<iostream>
using namespace std;

int main(void)
{
    string num1,num2;
    
    cout<<"请输入两个数字："<<endl;
    cin>>num1>>num2;
    
    cout<<"num1 + num2 = "<<big_data_add(num1,num2)<<endl;
    cout<<"num1 - num2 = "<<big_data_sub(num1,num2)<<endl;
    cout<<"num1 * num2 = "<<big_data_mul(num1,num2)<<endl;
    cout<<"num1 / num2 = "<<big_data_div(num1,num2)<<endl;
    return 0;
}
