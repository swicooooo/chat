// #include "Redis.h"

#include <cassert>

/// @brief 测试redis线程池
// void testRedisPool()
// {
//     Redis redis;
//     assert(redis.connect());
//     assert(redis.set("blogwebsite","llfc.club"));
//     std::string value="";
//     assert(redis.get("blogwebsite", value) );
//     assert(redis.existsKey("blogwebsite"));
//     assert(redis.del("blogwebsite"));
//     redis.close();
// }

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>

//connection ------------------count is: 29161
#define ROUNDS 5
#define CONNECTIONS_PER_ROUND 100000
void testConn()
{
      for (int i = 0; i < ROUNDS; i++) {
        std::cout << "Round " << i + 1 << "...\n";
        int clientfd[CONNECTIONS_PER_ROUND]={0};
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < CONNECTIONS_PER_ROUND; j++) {
            clientfd[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (clientfd[i] == -1) {
                std::cerr << "create socket error" << std::endl;
                exit(-1);
            }

            sockaddr_in server;
            memset(&server, 0, sizeof(sockaddr_in));
            server.sin_family = AF_INET;
            server.sin_port = htons(8000);
            server.sin_addr.s_addr = inet_addr("127.0.0.1");

            if (-1 == connect(clientfd[i], (sockaddr *)&server, sizeof(sockaddr_in))) {
                std::cout << "connect error" << std::endl;
                close(clientfd[i]);
                exit(-1);
            }

            // Connection established, do something (e.g., send/recv data)
            // For this example, we'll just close the connection
            
        }
        for (int j = 0; j < CONNECTIONS_PER_ROUND; j++)
        {
            close(clientfd[i]);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;
        std::cout << "Round " << i + 1 << " complete. Elapsed time: " << elapsed_time.count() << " seconds.\n";
    }
}

int main(int argc, char const *argv[])
{
    testConn();
    return 0;
}
