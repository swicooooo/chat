#include "ChatServer.h"

int main()
{
    EventLoop loop;
    InetAddress listenAddr(6000);
    ChatServer server(&loop, listenAddr, "main");
    server.start();
    loop.loop();
}