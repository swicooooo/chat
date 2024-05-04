#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <hiredis/hiredis.h>

class RedisConnPool
{
public:
    static void init(std::size_t poolSize, const char *host, int port, const char *pwd); // 初始化redis连接参数
    static RedisConnPool* instance();   // 获取实例

    redisContext* getConnection();
    void returnConnection(redisContext *context);
    void close();
private:
    RedisConnPool(std::size_t poolSize,const char *host,int port,const char *pwd);
    ~RedisConnPool();
    std::atomic_bool stop_;
    std::queue<redisContext*> connections_;
    std::mutex mutex_;
    std::condition_variable cond_;
};
