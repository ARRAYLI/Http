/*************************************************************************
	> File Name: sql.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 09时15分57秒
 ************************************************************************/

#ifndef _SQL_H
#define _SQL_H

#include<iostream>
#include<string.h>
#include<mysql/mysql.h>
using namespace std;

class SqlConnector
{
public:
    SqlConnector(const string _user = "root",
                 const string _passwd = "lzj201511",
                 const string _ip = "127.0.0.1",
                 const string _db = "http",
                 const int &_port = 3306);

    ~SqlConnector();
    bool connect();
    bool select();
    bool insert(const string &name,
                const string &sex,
                const string &hobby,
                const string &school);
    //bool delete_data();
private:
    MYSQL* connector;
    string user;
    string passwd;
    string ip;
    string db;
    int port;
};




#endif
