#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H

#include<string>
#include <vector>
using namespace std;

class offlineMsgModel
{
public:
    //存储用户的离线消息
    void insert(int userId, string msg);

    //删除用户离线消息
    void remove(int userid);

    //查询用户的离线消息
    vector<string> query(int userId);
};



#endif