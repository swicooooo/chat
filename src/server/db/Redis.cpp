#include "Redis.h"

#include <mymuduo/Logger.h>
#include <thread>

Redis::Redis(): subscribeContext_(nullptr), publishContext_(nullptr)
{}

Redis::~Redis()
{
    if(subscribeContext_ != nullptr) {
        redisFree(subscribeContext_);
    }
    if(publishContext_ != nullptr) {
        redisFree(publishContext_);
    }
}

bool Redis::connect()
{
    subscribeContext_ = redisConnect("127.0.0.1", 6379);
    if(subscribeContext_ == nullptr) {
        LOG_ERROR("%s:%d: redis connect error",__FILE__,__LINE__);
        return false;
    }  
    publishContext_ = redisConnect("127.0.0.1", 6379);
    if(publishContext_ == nullptr) {
        LOG_ERROR("%s:%d: redis connect error",__FILE__,__LINE__);
        return false;
    }   

    // 开辟独立线程，作观察者进行消息通知
    std::thread([&](){
        observerMessage();
    }).detach();

    return true;
}

bool Redis::publish(int channel, std::string msg)
{
    // 在redisCommand中不能"publish %d %s", channel,msg.c_str(), 会导致乱码
    redisReply* reply = (redisReply*)redisCommand(publishContext_,"publish %d %s", channel,msg);
    if(reply == nullptr) {
        LOG_ERROR("%s:%d: redis publish error",__FILE__,__LINE__);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

// 不直接使用redisCommand，是因为subscribe会堵塞当前线程
// 分命令可以先返回命令结果，在observerMessage中接受结果
bool Redis::subscribe(int channel)
{
    // 将order缓存到context中
    if(REDIS_ERR == redisAppendCommand(subscribeContext_,"subscribe %d", channel)) {
        LOG_ERROR("%s:%d: redis AppendCommand error",__FILE__,__LINE__);    
        return false;
    }
    // 从context的缓存中提取order并发送给服务器
    int done = 0;
    while (!done) {
        if(REDIS_ERR == redisBufferWrite(subscribeContext_,&done)) {
            LOG_ERROR("%s:%d: redis BufferWrite error",__FILE__,__LINE__);    
            return false;
        }
    }
    return true;
}

bool Redis::unsubscribe(int channel)
{
        // 将order缓存到context中
    if(REDIS_ERR == redisAppendCommand(subscribeContext_,"unsubscribe %d", channel)) {
        LOG_ERROR("%s:%d: redis AppendCommand error",__FILE__,__LINE__);    
        return false;
    }
    // 从context的缓存中提取order并发送给服务器
    int done = 0;
    while (!done) {
        if(REDIS_ERR == redisBufferWrite(subscribeContext_,&done)) {
            LOG_ERROR("%s:%d: redis BufferWrite error",__FILE__,__LINE__);    
            return false;
        }
    }
    return true;
}

void Redis::observerMessage()
{
    redisReply *reply = nullptr;
    while(REDIS_OK == redisGetReply(subscribeContext_,(void**)&reply)) {
        // reply里面返回的数据有三个 messgae,channel,实际消息,有消息则调用通知回调
        if(reply!=nullptr && reply->element[2]!=nullptr && reply->element[2]->str!=nullptr) {
            notifyHandler_(atoi(reply->element[1]->str),reply->element[2]->str);
        }
        freeReplyObject(reply);
    }
}

void Redis::initNotifyHandler(redisHandler notifyHandler)
{
    notifyHandler_ = notifyHandler;
}
