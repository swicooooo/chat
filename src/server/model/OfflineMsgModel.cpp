#include "OfflineMsgModel.h"

#include <mymuduo/Logger.h>

OfflineMsgModel::OfflineMsgModel()
{
    if(!mysql_.connect()) {
        LOG_ERROR("%s:%d mysql init error: %d", __FILE__, __LINE__, errno);
    }
}

void OfflineMsgModel::insert(int userid, std::string msg)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values(%d,'%s')",userid, msg.c_str());
    mysql_.update(sql);
}

void OfflineMsgModel::remove(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid=%d",userid);
    mysql_.update(sql);
}

std::vector<std::string> OfflineMsgModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid=%d", userid);
    std::vector<std::string> vec;
    MYSQL_RES *res = mysql_.query(sql);
    if(res != nullptr) {
        MYSQL_ROW row;
        while ((row=mysql_fetch_row(res)) != nullptr) {
            vec.push_back(row[0]);
        }
        mysql_free_result(res);
    }
    return vec;
}
