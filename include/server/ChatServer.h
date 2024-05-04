#pragma once

#include <mymuduo/TcpServer.h>

/// @brief 
class ChatServer
{
public:
    ChatServer(EventLoop* loop,const InetAddress& listenAddr,const std::string& nameArg);
    void start() { server_.start(); }

private:
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn,Buffer *buffer,Timestamp timestamp);

    TcpServer server_;
    EventLoop *loop_;
};