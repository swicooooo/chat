#include "ChatServer.h"
#include "ChatService.h"

#include <json.hpp>
#include <gperftools/tcmalloc.h>

ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    : server_(loop, listenAddr, nameArg),
      loop_(loop)
{
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this,std::placeholders::_1));
    server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    server_.setThreadNum(4);    // 五个线程
}

int total = 0;
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    std::cout << "------------------count is: " << total++ << std::endl;

    if(!conn->connected()) {
        ChatService::getInstance()->closeClientException(conn);
        conn->shutdown();   // 关闭这条通信链接
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp timestamp)
{
    // 使用内存池分配和回收buffer
    void *ptr = tc_malloc(sizeof(std::string));
    std::string* data = new(ptr)std::string();

    *data = buffer->retrieveAllAsString();
    nlohmann::json json = nlohmann::json::parse(*data);
    tc_free(ptr);
    // 解耦网络模块和业务模块
    auto handler = ChatService::getInstance()->getHandler(json["msgid"].get<int>());
    handler(conn, json, timestamp);
}
