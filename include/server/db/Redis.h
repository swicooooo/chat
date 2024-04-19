#pragma once

#include <string>
#include <functional>
#include <hiredis/hiredis.h>

/// @brief redis做消息中间件，解耦服务器间的通信
class Redis
{
public:
    using redisHandler = std::function<void(int channel,std::string msg)>;
    Redis();
    ~Redis();

    bool connect();
    void close();

    /// 发布订阅--消息队列
    bool publish(int channel, std::string msg);     // 发布
    bool subscribe(int channel);                    // 订阅
    bool unsubscribe(int channel);                  // 取消订阅
    void observerMessage();                         // 独立线程中接收订阅通道的消息
    void initNotifyHandler(redisHandler handler);   // 初始化通知处理器

    /// 缓存服务
    bool get(const std::string &key,std::string &value);
    bool set(const std::string &key,const std::string &value);
    bool del(const std::string &key);
    bool existsKey(const std::string &key);

private:
    redisContext *cacheContext_;        // redis缓存客户端
    redisContext *subscribeContext_;    // 负责subscribe消息
    redisContext *publishContext_;      // 负责publish消息
    redisHandler notifyHandler_;        // 负责向业务层上报消息
};

