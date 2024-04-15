#pragma once

#include <vector>
#include <string>

#include "db.h"
#include <User.h>

/// @brief friend表的好友信息操作类
class FriendModel
{
public:
    FriendModel();
    void insert(int userid, int friendid);      // 添加好友
    std::vector<User> query(int userid); // 返回用户好友列表
private:
   MySQL mysql_;
};