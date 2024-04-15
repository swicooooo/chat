#pragma once

#include "Group.h"
#include "db.h"

class GroupModel
{
public:
    GroupModel();
    bool createGroup(Group &group);     // 创建群组
    bool addGroup(int userid, int groupid, std::string role);       // 加入群组
    std::vector<Group> queryGroups(int userid);                     // 查询用户所在群组
    std::vector<int> queryGroupUserIds(int userid, int groupid);    // 查询群组其他成员userid
private:
   MySQL mysql_;
};


