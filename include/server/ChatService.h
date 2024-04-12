#pragma once

#include <unordered_map>
#include <functional>
#include <mymuduo/TcpServer.h>
#include <json.hpp>

#include "UserModel.h"

// 处理消息的事件回调类型
using MsgHandler = std::function<void(const TcpConnectionPtr&,nlohmann::json&,Timestamp)>;

class ChatService
{
public:
    static ChatService* getInstance();  // 获取单例接口函数

    MsgHandler getHandler(int msgid);   // 获取msgid对应消息处理器
    void login(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);    // 处理登录业务
    void reg(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);      // 处理注册业务
private:
    ChatService();
    std::unordered_map<int, MsgHandler> msgHandlers_;
    UserModel userModel_;   // 数据操作类对象
};