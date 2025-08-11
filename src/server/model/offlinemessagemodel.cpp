#include "offlinemessagemodel.hpp"
#include "db.h"



//存储用户的离线消息
void offlineMsgModel::insert(int userId, string msg)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into OfflineMessage values('%d', '%s')",userId, msg.c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//删除用户离线消息
void offlineMsgModel::remove(int userid)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from OfflineMessage where userid=%d",userid);

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//查询用户的离线消息
vector<string> offlineMsgModel::query(int userId)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select message from OfflineMessage where userid = %d", userId);

    vector<string> vec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES * res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res))!= nullptr)
            {
                //把userid用户的所有的离线消息放入vec中返回
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }    
    }
    return vec;
}