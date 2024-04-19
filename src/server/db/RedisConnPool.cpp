#include "RedisConnPool.h"

#include <mymuduo/Logger.h>

static std::size_t poolSize_;
static const char *host_;
static int port_;
static const char *pwd_;

void RedisConnPool::init(std::size_t poolSize, const char *host, int port, const char *pwd)
{
    poolSize_ = poolSize;
    host_ = host;
    port_ = port;
    pwd_ = pwd;
}

RedisConnPool * RedisConnPool::instance()
{
    static RedisConnPool redisConnPool(poolSize_,host_,port_,pwd_);
    return &redisConnPool;
}

redisContext *RedisConnPool::getConnection()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock,[&](){
        if(stop_) {
            return true;
        }
        return !connections_.empty();
    }); // 如果cond没有被唤醒，则它会解开lock锁，并阻塞
    if(stop_) {
        return nullptr;
    }
    auto context = connections_.front();
    connections_.pop();
    return context;
}

void RedisConnPool::returnConnection(redisContext *context)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(stop_) {
        return;
    }
    connections_.push(context);
    cond_.notify_one();
}

void RedisConnPool::close()
{
    stop_ = true;
    cond_.notify_all();
}

RedisConnPool::RedisConnPool(std::size_t poolSize, const char *host, int port, const char *pwd)
    :stop_(false)
{
    std::printf("------------%s %d\n", host,port);
    for (size_t i = 0; i < poolSize_; i++) {
        // 创建redis context
        auto *context = redisConnect(host,port);
        if(context==nullptr) {
            LOG_ERROR("%s:%d: redis pool connect error",__FILE__,__LINE__);
            continue;
        }
        // 执行redis auth
        auto reply = (redisReply*)redisCommand(context,"auth %s",pwd);
        if(reply->type == REDIS_REPLY_ERROR) {
            LOG_ERROR("%s:%d: redis pool auth error",__FILE__,__LINE__);
            freeReplyObject(reply);
            continue;
        }
        // 加入redis connections
        freeReplyObject(reply);
        connections_.push(context);
    }
}

RedisConnPool::~RedisConnPool()
{
    std::lock_guard<std::mutex> lock(mutex_);
    while(!connections_.empty()) {
        connections_.pop();
    }
}