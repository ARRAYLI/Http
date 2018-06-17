#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include"Calc.h"
using namespace std;

bool get_arg(char* buf)
{
	char* method = NULL;
	char* arg_string = NULL;
	char* content_length = NULL;

	method = getenv("METHOD");
	if(method && strcasecmp(method, "GET") == 0){
		arg_string = getenv("QUERY_STRING");
		if( !arg_string)
			return false;
		strcpy(buf, arg_string);
	}
	else if (method && strcasecmp(method, "POST") == 0){
		content_length = getenv("CONTENT_LENGTH");
		if( ! content_length){
			return false;
		}
		int i = 0;
		char c = 0;
		int nums = atoi(content_length);
		for(; i < nums; ++i){
			read(0, &c, 1);
			buf[i] = c;
		}
		buf[i] = 0;
		return true;
	}
	return false;
}

void send_404()
{
	string stat = "HTTP/1.0 404 NOT FOUND\r\n";
	cout << stat;
	string type = "ContenType: text/html\r\n";
	cout << type;
    string blank = "\r\n";
    cout<<blank;
}

void send_200()
{
	string stat = "HTTP/1.0 200 OK\r\n";
	cout << stat;
	string type = "ContenType: text/html\r\n";
	cout << type;
    string blank = "\r\n";
    cout<<blank;
}


void math_cal(char* buf)
{
	char* start = buf;
	char* arg[2];
	int idx = 0;
	while(*start && idx < 2){
		if(*start == '='){
			start++;
			arg[idx++] = start;
		}
		if( *start == '&'){
			*start = '\0';
		}
		start++;
	}
    /*
	int data1 = atoi(arg[0]);
	int data2 = atoi(arg[1]);
	send_200();
	cout << "<HTML><BODY> <H1> data1 + data2 = " << data1 + data2 <<"</H1>";
	cout << "<H1> data2 - data2 = "<< data2 - data2 << "</H1>";
	cout << "<H1> data2 * data2 = "<< data2 * data2 << "</H1>";
	cout << "<H1> data2 / data2 = "<< data2 / data2 << "</H1>";
	cout << "</BODY></HTML>";
    */
    string data1 = string(arg[0]);
	string data2 = string(arg[1]);
	send_200();
	cout << "<HTML><BODY> <H1> data1 + data2 = " << big_data_add(data1,data2)<<"</H1>";
	cout << "<H1> data2 - data2 = "<< big_data_sub(data1,data2) << "</H1>";
	cout << "<H1> data2 * data2 = "<<big_data_mul(data1,data2) << "</H1>";
	cout << "<H1> data2 / data2 = "<<big_data_div(data1,data2) << "</H1>";
	cout << "</BODY></HTML>";
    
}

int main()
{
	char buf[1024];
	get_arg(buf);
	math_cal(buf);
	return 0;
}
