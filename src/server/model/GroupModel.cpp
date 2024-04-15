#include "GroupModel.h"

#include <mymuduo/Logger.h>

GroupModel::GroupModel()
{
    if(!mysql_.connect()) {
        LOG_ERROR("%s:%d mysql init error: %d", __FILE__, __LINE__, errno);
    }
}

bool GroupModel::createGroup(Group &group)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')",
        group.name.c_str(),group.desc.c_str());

    if(mysql_.update(sql)) {
        group.id = mysql_insert_id(mysql_.getConn());
        return true;
    }
    return false;
}

bool GroupModel::addGroup(int userid, int groupid, std::string role)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser(groupid,userid,grouprole) values('%d','%d','%s')",
        groupid, userid, role.c_str());

    if(mysql_.update(sql)) {
        return true;
    }
    return false;
}

std::vector<Group> GroupModel::queryGroups(int userid)
{
    
    char sql[1024] = {0};
    sprintf(sql, "select * from allgroup a inner join \
        groupuser b on b.groupid=a.groupid where b.userid=%d", userid);
    
    std::vector<Group> groupVec;
    MYSQL_RES *res = mysql_.query(sql);
    // 组装group信息
    if(res != nullptr) {
        MYSQL_ROW row;
        while ((row=mysql_fetch_row(res)) != nullptr) {
            Group group;
            group.id = atoi(row[0]);
            group.name = row[1];
            group.desc = row[2];
            groupVec.push_back(group);
        }
        mysql_free_result(res);
    }
    // 组装group下的users信息
    for(Group &group: groupVec) {
        sprintf(sql, "select a.id,a.name,a.state,b.grouprole from user a inner join \
            groupuser b on b.userid=a.id where b.groupid=%d", group.id);
        
        MYSQL_RES *res = mysql_.query(sql);
        // 组装group信息
        if(res != nullptr) {
            MYSQL_ROW row;
            while ((row=mysql_fetch_row(res)) != nullptr) {
                GroupUser user;
                user.id = atoi(row[0]);
                user.name = row[1];
                user.state = row[2];
                user.role = row[3];
                group.groupUsers.push_back(user);
            }
            mysql_free_result(res);
        }
    }

    return groupVec;
}

std::vector<int> GroupModel::queryGroupUserIds(int userid, int groupid)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid=%d and userid!=%d", groupid, userid);
    
    std::vector<int> idVec;
    MYSQL_RES *res = mysql_.query(sql);
    // 组装group信息
    if(res != nullptr) {
        MYSQL_ROW row;
        while ((row=mysql_fetch_row(res)) != nullptr) {
            idVec.push_back(atoi(row[0]));
        }
        mysql_free_result(res);
    }
    return idVec;
}
