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

            // 查询该用户是否有离线消息,有则发送并删除
            auto msgs = offlineMsgModel_.query(user.id);
            if(!msgs.empty()) {
                resp["offlinemsg"] = msgs;
                offlineMsgModel_.remove(user.id);   
            }

            // 查询用户好友信息并返回
            auto friends = friendModel_.query(user.id);
            if(!friends.empty()) {
                std::vector<std::string> friendVec;
                for(auto f: friends) {
                    nlohmann::json js;
                    js["id"] = f.id;
                    js["name"] = f.name;
                    js["state"] = f.state;
                    friendVec.push_back(js.dump());
                }
                resp["friends"] = friendVec;
            }

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

void ChatService::oneChat(const TcpConnectionPtr &conn, nlohmann::json &js, Timestamp timestamp)
{
    int toid = js["to"].get<int>();
    {
        std::lock_guard<std::mutex> lock(connMutex_);
        auto it = userConns_.find(toid);
        if(it != userConns_.end()) {
            // toid在线，服务器主动推送消息给toid用户
            it->second->send(js.dump());
            return;
        }
    }
    // toid离线，服务器存储离线消息
    offlineMsgModel_.insert(toid, js.dump());
}

void ChatService::addFriend(const TcpConnectionPtr & conn, nlohmann::json & js, Timestamp timestamp)
{
    friendModel_.insert(js["userid"].get<int>(), js["friendid"].get<int>());
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

void ChatService::reset()
{
    // 重置所有用户的状态
    userModel_.resetState();
}

ChatService::ChatService()
{
    msgHandlers_.insert({LOGIN_MSG, std::bind(&ChatService::login, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    msgHandlers_.insert({REG_MSG, std::bind(&ChatService::reg, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    msgHandlers_.insert({ONE_CHAT_MSG, std::bind(&ChatService::oneChat, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    msgHandlers_.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addFriend, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});

}