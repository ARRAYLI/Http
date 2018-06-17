/*************************************************************************
	> File Name: Calc.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月13日 星期三 21时04分24秒
 ************************************************************************/

#include"Calc.h"

//#define __DEBUG__

/* 超大数加法 */
string big_data_add(string num1,string num2)
{
    /* 判断两个数哪个数字长，大数记为 num1,小数记为 num2;同一转换为长数字加上短数字 */
    if(num1.length() < num2.length())
    {
        /* 这里使用 STL 的 string 类的交换方法 */
        num1.swap(num2);
        /*
        string temp  = num1;
        num1 = num2;
        num2 = temp;
        */
    }

    /* 获取 num1 和 num1 超大数的长度 */
    int len1 = num1.length();  /* 较长的数字的长度 */
    int len2 = num2.length();  /* 较短的数字长度 */
    int carry = 0;             /* 进位 数字  */
    string result; 
    int minlen = len2-1;
    int maxlen = len1-1;


    /* 先从较短的数字开始和较长数字相加 */
    for(int i=0;i<len2;i++)
    {
        /* 求出两个数字的最低位数字之和 */
       int sum = (num1[maxlen] - '0') + (num2[minlen] - '0') + carry; 
    
        maxlen--;
        minlen--;

        /* 求出两个数字之间是否有进位，进位数字是多少 */
        carry = sum / 10;
        
        /* 求出两个数字的和的个位数 */
        int a = sum % 10;

        result.push_back(a+'0');
    }

    /* 加完后，计算较长数字的剩余位数的运算 */
    for(int i = len2;i<len1;i++)
    {
        int sum = num1[maxlen] - '0' + carry;
       
        maxlen--;
        carry = sum / 10;

        int a = sum % 10;

        result.push_back(a+'0');
    }
   
    /* 判断长数的最高位是否要向前进一位，如果进位的话 */
    if( carry != 0 )
        result.push_back(carry+'0');
    
    /* 不进位的话,给字符串逆序，低位低地址，高位高地址 */
    reverse(result.begin(),result.end()); 

    /* 判断两个超大数字进行运算后的结果是否为 0 */
    if(result.empty())
    {
       result += '0';
    }
    return result;
}
   
/* 超大数减法 */
string big_data_sub(string num1,string num2)
{
    /*
    cout<<"num1.length() = "<<num1.length()<<endl;
    cout<<"num2.length() = "<<num2.length()<<endl;
    */

    /* 默认两个超大数字之差大于 0 */
    char sign = '+';
    /* 把较大数放在 num1 的位置，较小的数放在 Num2 的位置上 */
    if(num1.length() < num2.length())
    {
        /* 这里使用 STL 的 string 类的交换方法 */
        num1.swap(num2);
        /*
        string temp = num1;
        num1 = num2;
        num2 = temp;
        */
        sign = '-';
        // cout<<"-------------------1"<<endl;
    }
    
    /* 如果两个数字的长度相同，则判断两个数字的每一位数字，知道找到一个数字能判断出连个数字大小为止，进程数字交换 */

    else if(num1.length() == num2.length())
    {
        for(int i = 0;i<num1.length();i++)
        {
            /* 如果当前位置的数字 num1 比 num1 大，那么直接跳出循环,不用进行交换 */
            if(num1[i] > num2[i])
            {
                break;    
            }
            /* 如果当前位置的数字 num1 < num2 的话，那么交换值 */
            else if(num1[i] < num2[i])
            {
                /*
                string temp =  num1;
                num1 = num2;
                num2 = temp;
                */
                /* 这里使用 STL 的 string 类的交换方法 */
                num1.swap(num2);
                sign = '-';
                // cout<<"-------------------2"<<endl;
                break;
            }
            /* 如果当前位置的数字相同，继续向后遍历比较两个数字的当前位置的数值，直到找到不相同的数字位置 */
            else
                continue;
        }

    }
     
    //cout<<"num1.length() = "<<num1.length()<<endl;
    //cout<<"num2.length() = "<<num2.length()<<endl;
    string result;              /* 两个超大数之差的结果 */
    int len1 = num1.length();   /* 较大数字的长度 */
    int len2 = num2.length();   /* 较小数字的长度 */
    int borrow = 0;             /* 在进行两数做差时，借位数字 */
    
    /* 两数字做差操作前，先给两个字符串逆序 */
    reverse(num1.begin(),num1.end());
    reverse(num2.begin(),num2.end());
   
   
    /* 先给以较短数字为长度的两个超大数据进行做差 */
    for(int i=0;i<len2;i++)
    {
       int r = (num1[i] - '0') - (num2[i] - '0') - borrow;
        borrow = 0;
        /* 如果两个数字之差的结果小于 0，则产生借位*/
        if( r < 0 )
        {
            r += 10;
            borrow = 1;
        }
        result.push_back(r+'0');
    }
   
    /* 接下来给两个数字中较长的数字剩下的位数继续进行做差 */
    for(int i = len2;i<len1;i++)
    {
       int r = num1[i] -'0' - borrow;
        borrow = 0;
        if(r < 0)
        {
            r += 10;
            borrow = 1;
        }
        result.push_back(r+'0');
    }

    /* 做完差后，清除结果数字的有效数字前面的所有 0 */
    for(int i = len1 -1;i>=0;i--)
    {
       if(result[i] == '0')
        {
           result.erase(result.begin()+i); 
        }
        else
            break;
    }
    
    /* 做完差后，给结果逆序 */
    reverse(result.begin(),result.end());

    // cout<<"-------------------3"<<endl;
    // cout<<"sign = "<<sign<<",reuslt ="<<result<<endl;
    /* 判断两个超大数的做差结果是否为负数，如果为负数的话，那么给结果前面加上 '-' */
    if(sign == '-')
    {
       result.insert(result.begin(),'-'); 
    }

    if(result.empty())
    {
       result += '0';
    }
    return result;
}

/* 超大数乘法 */
string big_data_mul(string num1,string num2)
{
    string result = "0";
   /* 首先判断两个超大数是否为空 */
    if(num1 == "0" || num2 == "0")
        return result;
    vector<string> tmpResult;
    int len1 = num1.length();
    int len2 = num2.length();
    int carry = 0;

    /* 给两个字符串逆序，从低地址出考试进行乘法运算 */
    reverse(num1.begin(),num1.end()); 
    reverse(num2.begin(),num2.end());

    /* 用第一个超大数的每一位与第二个超大数的每一位进行乘积运算 */
    for(int i=0;i<len1;i++) 
    {
        string str;

        for(int j=0;j<len2;j++)
        {
            int r = (num1[i] - '0') *(num2[j] - '0') + carry;
            /* 如果两个数字的乘积大于 10 的话，产生进位 */
            carry = r / 10; 
            int a = r - carry*10;

            str.push_back(a + '0');
        }
        /* 判断是否继续进位 */
        if(carry)
        {
            str.push_back(carry + '0'); 
        }
        /* 每次进位后，把进位数字置为 0，以便下次操*/
        carry = 0;

        /* 把每次计算的结果逆序，显示成正常的低地址高位 */
        reverse(str.begin(),str.end());

        /* 计算每次乘法操作的移位操作,给字符串的尾部加 '0' 来占位置 */
        for(int k=0;k<i;k++)
        {
           str.push_back('0'); 
        }
        /* 然后把结果添加到 tmpResult 中，进行下一次乘法操作 */
        tmpResult.push_back(str);
    }
    /* 对容器 tmpResult 中的所有字符串进行加法操作，获取两个超大数的乘积 */
    int size = tmpResult.size();
    for(int i=0;i<size;i++)
    {
       result = big_data_add(result,tmpResult[i]); 
    }

    /* 判断两个超大数字进行运算后的结果是否为 0 */
    if(result.empty())
    {
        result += '0';
    } 
    return result;
}

#ifdef __DEBUG__
/* 超大数除法 */

string big_data_div(string num1,string num2)
{
   string result;
    /* 先判断两个超大数字做除法是否大于 0 */
    
    result = big_data_sub(num1,num2);
    if(result[0] == '-')
    {
        result = "0";
       return  result;
    }
    
    result = "";
    int len1 = num1.size();
    stringstream stream;
    string dividend;

    for(int i=0;i<len1;i++)
    {
        dividend.push_back(num1[i]);  // 被除数 
        /* 从 9 到 0 试探性的找商，当余数不为负数时，为当前位置的值 */
       for(int j=9;j>=0;j--)
        {
            stream.str("");
            stream<<j;

            string s = stream.str();
            string sj = big_data_mul(num2,s);
            //cout<<"sj = "<<sj<<endl;
            string remind = big_data_sub(dividend,sj);
           // cout<<"remind = "<<remind<<endl;
            //cout<<"remind[0] = "<<remind[0]<<endl;
            if(remind[0] != '-')
            {
                cout<<"i = "<<endl;
               result.push_back(j+'0'); 
                cout<<"result = "<<endl;
                dividend = remind;
                break;
            }

        }

    }
    
    int size = result.length();
    /* 去掉商前面的 0 位 */
    for(int i=0;i<size;i++)
    {
       if(result[0] == '0')
        {
            result.erase(result.begin());
        }
        else
            break;
    }
    cout<<"result = "<<endl;
    /* 四舍五入 */
/*
    string s = big_data_sub(big_data_mul(dividend,"2"),num2);
    if(s[0] == '-') 
        result = big_data_add(result,"1");
*/
    return result;
}
#else 
/* 超大数除法 */

string big_data_div(string num1,string num2)
{
   string result;
    /* 先判断两个超大数字做除法是否大于 0 */
    
    result = big_data_sub(num1,num2);
    if(result[0] == '-')
    {
        result = "0";
       return  result;
    }
    
    result = "";
    int len1 = num1.size();
    stringstream stream;
    string dividend;

    for(int i=0;i<len1;i++)
    {
        dividend.push_back(num1[i]);  // 被除数 
        /* 从 9 到 0 试探性的找商，当余数不为负数时，为当前位置的值 */
       for(int j=9;j>=0;j--)
        {
            stream.str("");
            stream<<j;

            string s = stream.str();
            string sj = big_data_mul(num2,s);
            string remind = big_data_sub(dividend,sj);
            if(remind[0] != '-')
            {
               result.push_back(j+'0'); 
                dividend = remind;
                break;
            }

        }

    }
    
    int size = result.length();
    /* 去掉商前面的 0 位 */
    for(int i=0;i<size;i++)
    {
       if(result[0] == '0')
        {
            result.erase(result.begin());
        }
        else
            break;
    }
    /* 四舍五入 */
/*
    string s = big_data_sub(big_data_mul(dividend,"2"),num2);
    if(s[0] == '-') 
        result = big_data_add(result,"1");
*/
    return result;
}
#endif
