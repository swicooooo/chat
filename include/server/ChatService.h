#pragma once

#include <unordered_map>
#include <functional>
#include <mutex>
#include <mymuduo/TcpServer.h>
#include <json.hpp>

#include "UserModel.h"
#include "OfflineMsgModel.h"
#include "FriendModel.h"

// 处理消息的事件回调类型
using MsgHandler = std::function<void(const TcpConnectionPtr&,nlohmann::json&,Timestamp)>;

class ChatService
{
public:
    static ChatService* getInstance();  // 获取单例接口函数

    MsgHandler getHandler(int msgid);   // 获取msgid对应消息处理器
    void login(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);    // 处理登录业务
    void reg(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);      // 处理注册业务
    void oneChat(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);  // 处理一对一业务
    void addFriend(const TcpConnectionPtr& conn,nlohmann::json &js,Timestamp timestamp);// 处理添加好友业务

    void closeClientException(const TcpConnectionPtr& conn);// 处理客户端异常退出
    void reset();   //  服务器测试异常，业务重置方法
private:
    ChatService();
    std::unordered_map<int, MsgHandler> msgHandlers_;       // 存储业务处理方法
    std::unordered_map<int, TcpConnectionPtr> userConns_;   // 存储在线用户的链接
    std::mutex connMutex_;  // 保护userConns_在多线程下的访问
    UserModel userModel_;   // 数据操作类对象
    OfflineMsgModel offlineMsgModel_;   // 离线消息操作类对象 
    FriendModel friendModel_;           // 好友信息操作类对象
};