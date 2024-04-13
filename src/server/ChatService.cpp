#include "ChatService.h"
#include "Common.h"

#include <mymuduo/Logger.h>

ChatService *ChatService::getInstance()
{
    static ChatService chatService;
    return &chatService;
}

MsgHandler ChatService::getHandler(int msgid)
{
    if(msgHandlers_.find(msgid) == msgHandlers_.end()) {
        // 返回一个默认处理器，空操作
        return [&](const TcpConnectionPtr&,nlohmann::json&,Timestamp){
            LOG_ERROR("msgid: %d can not find handler!", msgid);
        };
    }
    return msgHandlers_[msgid];
}

void ChatService::login(const TcpConnectionPtr &conn, nlohmann::json &js, Timestamp timestamp)
{
    LOG_INFO("do login service!!!");
    User user = userModel_.query(js["id"].get<int>());
    nlohmann::json resp;
    if(user.id!=-1 && user.pwd==js["password"]) {
        // 如果该用户已在线，不允许重复登陆
        if(user.state == "online") {
            resp["msgid"] = LOGIN_MSG_ACK;
            resp["errno"] = 2;  // 用户已在线     
            resp["errmsg"] = "该账号已登录";
            conn->send(resp.dump());
        }else{
            {
                std::lock_guard<std::mutex> lock(connMutex_);
                userConns_.insert({user.id, conn});
            }
            // 登录成功，同时刷新状态
            user.state = "online";
            userModel_.updateState(user);

            resp["msgid"] = LOGIN_MSG_ACK;
            resp["errno"] = 0;    
            resp["id"] = user.id;
            resp["name"] = user.name;
            conn->send(resp.dump());
        }
        
    }else{
        resp["msgid"] = LOGIN_MSG_ACK;
        resp["errno"] = 1;  // 错误码，出错
        resp["errmsg"] = "用户名或密码错误";
        conn->send(resp.dump());
    }
}

void ChatService::reg(const TcpConnectionPtr &conn, nlohmann::json &js, Timestamp timestamp)
{
    LOG_INFO("do reg service!!!");
    User user;
    user.name = js["name"];
    user.pwd =  js["password"];

    bool flag = userModel_.insert(user);
    nlohmann::json resp;    // 返回客户端的响应对象
    if(flag) {
        resp["msgid"] = REG_MSG_ACK;
        resp["errno"] = 0;  // 错误码，未出错
        resp["id"] = user.id;
        conn->send(resp.dump());
    }else{
        resp["msgid"] = REG_MSG_ACK;
        resp["errno"] = 1;  // 错误码，出错
        resp["errmsg"] = "数据错误, 请重试";
        conn->send(resp.dump());
    }
}

void ChatService::closeClientException(const TcpConnectionPtr &conn)
{
    User user;
    // 从userConns_在线用户中删除
    for (auto it = userConns_.begin(); it != userConns_.end(); it++) {
        if(it->second = conn) {
                user.id = it->first;
            {
                std::lock_guard<std::mutex> lock(connMutex_);
                userConns_.erase(it);
            }
                break;
        }
    }
    if(user.id != -1) {
        user.state = "offline"; // 设置为offline
        userModel_.updateState(user);
    }
}

ChatService::ChatService()
{
    msgHandlers_.insert({LOGIN_MSG, std::bind(&ChatService::login, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    msgHandlers_.insert({REG_MSG, std::bind(&ChatService::reg, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
}