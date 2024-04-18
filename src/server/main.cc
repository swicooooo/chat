#include "ChatServer.h"
#include "signal.h"
#include "ChatService.h"

#include "Redis.h"

// 服务器ctrl+c挂掉后，处理user的状态信息
void resetHandler(int)
{
    ChatService::getInstance()->reset();
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "command invaild example: ./ExeNAME  IpAddress  port" << std::endl;
        exit(-1);
    }

    //解析IP地址和端口号
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);
    signal(SIGINT, resetHandler);

    EventLoop loop;
    InetAddress listenAddr(port,ip);

    // signal(SIGINT, resetHandler);

    // EventLoop loop;
    // InetAddress listenAddr(6000);

    ChatServer server(&loop, listenAddr, "main");
    server.start();
    loop.loop();

}

 