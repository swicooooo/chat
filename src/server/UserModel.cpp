#include "UserModel.h"
#include "db.h"

#include <iostream>

bool UserModel::insert(User &user)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,password,state) values('%s','%s','%s')",
        user.name.c_str(),user.pwd.c_str(),user.state.c_str());

    MySQL mysql;
    if(mysql.connect() && mysql.update(sql)) {
        user.id = mysql_insert_id(mysql.getConn());
        return true;
    }
    return false;
}