/*************************************************************************
	> File Name: sql.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月12日 星期二 09时16分03秒
 ************************************************************************/

#include"sql.h"

SqlConnector::SqlConnector(const string _user,
                 const string _passwd,
                 const string _ip,
                 const string _db,
                 const int& _port)
    :user(_user)
    ,passwd(_passwd)
    ,ip(_ip)
    ,db(_db)
    ,port(_port)
{
    connector = mysql_init(NULL);
}

 SqlConnector::~SqlConnector()
 {
    mysql_close(connector);    
 }

bool SqlConnector::connect()
{
    if(mysql_real_connect(connector,ip.c_str(),user.c_str(),passwd.c_str(),db.c_str(),port,NULL,0))
    {
        return true;
    }
    return false;
}

bool SqlConnector::select()
{
    string select("select *from student"); 
    
    if(mysql_query(connector,select.c_str()) == 0)
    {
        MYSQL_RES* res = mysql_store_result(connector);
        if(res)
        {
            /* get the row of the query */
            int rows = mysql_num_rows(res);
            /* get the field of the query result */
            int fields = mysql_num_fields(res);
            
            MYSQL_FIELD * fd = NULL;
            /* get the name of field */
            for( ; fd = mysql_fetch_field(res); )
            {
               cout<<fd->name<<"--------";
            }
            cout<<"<br>";

            /* print rows and fields */
            int i = 0;
            for(; i< rows; i++)
            {
               MYSQL_ROW row = mysql_fetch_row(res);
                int j = 0;
                for( ; j<fields; j++ )
                {
                   cout<<row[j]<<"--------";
                }
                cout<<"<br>";
            }
            return true;
        }
    }
    return false;
}

#ifdef __DEBUG__
bool SqlConnector::select()
{
	std::string select("select * from student");

	if( mysql_query( connector, select.c_str()) == 0)
	{
		MYSQL_RES *res = mysql_store_result(connector);

		if(res)
		{
			// get the row of the query result
			int rows = mysql_num_rows(res);
			//get the field of the query result 
			int fields = mysql_num_fields(res);
			MYSQL_FIELD *fd = NULL;

			// get the name of the field
			for(; fd = mysql_fetch_field(res); )
			{
				cout << fd->name << "--";
			}

			cout << "<br>";
			// print row and field 
			int i = 0;
			for (; i < rows; ++i)
			{
				MYSQL_ROW row = mysql_fetch_row(res);
				int j = 0;
				for(; j < fields; j++)
					cout << row[j] << "--";

				cout << "<br>";
			}
			return true;
		}
	}
	return false;
}

#endif



bool SqlConnector::insert(const string &name,
                const string &sex,
                const string &hobby,
                const string &school)
{
    
    string insert("insert into student(name,sex,hobby,school) values('"); 
    insert += name;
    insert += "','";
    insert += sex;
    insert += "','";
    insert += hobby;
    insert += "','";
    insert += school;
    insert += "')";
    
    //cout<<"insert = "<<insert<<endl;
    if(mysql_query(connector,insert.c_str()) == 0)
        return true;

    return false;
}

