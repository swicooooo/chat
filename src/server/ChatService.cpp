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
}

void ChatService::reg(const TcpConnectionPtr &conn, nlohmann::json &js, Timestamp timestamp)
{
    LOG_INFO("do login service!!!");
}

ChatService::ChatService()
{
    msgHandlers_.insert({LOGIN_MSG, std::bind(&ChatService::login, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    msgHandlers_.insert({REG_MSG, std::bind(&ChatService::reg, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
}