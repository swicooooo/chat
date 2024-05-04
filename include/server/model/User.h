#pragma once

#include <string>

/// @brief orm模型， User表的映射类
struct User
{
    int id = -1;
    std::string name = "";
    std::string pwd = "";
    std::string state = "offline";
};
