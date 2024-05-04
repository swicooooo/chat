#include "UserModel.h"

#include <iostream>
#include <mymuduo/Logger.h>

UserModel::UserModel()
{
    if(!mysql_.connect()) {
        LOG_ERROR("%s:%d mysql init error: %d", __FILE__, __LINE__, errno);
    }
}

bool UserModel::insert(User &user)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,password,state) values('%s','%s','%s')",
        user.name.c_str(),user.pwd.c_str(),user.state.c_str());

    if(mysql_.update(sql)) {
        user.id = mysql_insert_id(mysql_.getConn());
        return true;
    }
    return false;
}

User UserModel::query(int id)
{
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id=%d", id);
    MYSQL_RES *res = mysql_.query(sql);
    if(res != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if(row != nullptr)  {
            User user;
            user.id = atoi(row[0]);
            user.name = row[1];
            user.pwd = row[2];
            user.state = row[3];
            mysql_free_result(res);
            return user;
        }
    }

    return User();
}

bool UserModel::updateState(User user)
{
    char sql[1024] = {0};
    sprintf(sql, "update user set state='%s' where id=%d", user.state.c_str(), user.id);

    if(mysql_.update(sql)) {
        return true;
    }
    return false;
}

void UserModel::resetState()
{
    char sql[1024] = "update user set state='offline' where state='online'";
    mysql_.update(sql);
}
