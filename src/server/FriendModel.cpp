#include "FriendModel.h"

#include <mymuduo/Logger.h>

FriendModel::FriendModel()
{
    if(!mysql_.connect()) {
        LOG_ERROR("%s:%d mysql init error: %d", __FILE__, __LINE__, errno);
    }
}

void FriendModel::insert(int userid, int friendid)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into friend(userid,friendid) values('%d','%d')",userid, friendid);
    mysql_.update(sql);
}

std::vector<User> FriendModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid=a.id where b.userid=%d", userid);
    std::vector<User> vec;
    MYSQL_RES *res = mysql_.query(sql);
    if(res != nullptr) {
        MYSQL_ROW row;
        while ((row=mysql_fetch_row(res)) != nullptr) {
            User user;
            user.id = atoi(row[0]);
            user.name = row[1];
            user.state = row[2];
            vec.push_back(user);
        }
        mysql_free_result(res);
    }
    return vec;
}
