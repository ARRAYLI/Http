/*************************************************************************
	> File Name: Calc.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 18时02分48秒
 ************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

/* 超大数加法 */
string big_data_add(string num1,string num2);
   
/* 超大数减法 */
string big_data_sub(string num1,string num2);

/* 超大数乘法 */
string big_data_mul(string num1,string num2);

/* 超大数除法 */
string big_data_div(string num1,string num2);

#endif
