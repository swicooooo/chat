#pragma once

#include <string>

#include "User.h"

struct GroupUser: public User
{
    std::string role;
};
