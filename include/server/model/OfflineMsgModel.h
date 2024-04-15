#pragma once

#include <string>
#include <vector>

#include "db.h"

/// @brief offline表的离线数据操作类
class OfflineMsgModel
{
public:
    OfflineMsgModel();
    void insert(int userid, std::string msg);   // 存储用户离线消息
    void remove(int userid);                    // 删除用户离线消息
    std::vector<std::string> query(int userid); // 查询用户离线消息
private:
   MySQL mysql_;
};