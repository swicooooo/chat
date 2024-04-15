#pragma once

#include <string>
#include <vector>

#include "GroupUser.h"

struct Group
{
    int id= - 1;
    std::string name = "";
    std::string desc = "";
    std::vector<GroupUser> groupUsers;
};
