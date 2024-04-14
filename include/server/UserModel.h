#pragma once

#include "User.h"
#include "db.h"

/// @brief User表的数据操作类
class UserModel
{
public:
   UserModel();
   bool insert(User &user);
   User query(int id);
   bool updateState(User user);
   void resetState();   // 重置用户状态信息
private:
   MySQL mysql_;
};

