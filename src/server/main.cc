#include "ChatServer.h"
#include "signal.h"
#include "ChatService.h"

// 服务器ctrl+c挂掉后，处理user的状态信息
void resetHandler(int)
{
    ChatService::getInstance()->reset();
    exit(0);
}

int main()
{
    signal(SIGINT, resetHandler);

    EventLoop loop;
    InetAddress listenAddr(6000);
    ChatServer server(&loop, listenAddr, "main");
    server.start();
    loop.loop();
}