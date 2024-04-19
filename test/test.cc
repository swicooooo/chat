#include "Redis.h"

#include <cassert>

/// @brief 测试redis线程池
void testRedisPool()
{
    Redis redis;
    assert(redis.connect());
    assert(redis.set("blogwebsite","llfc.club"));
    std::string value="";
    assert(redis.get("blogwebsite", value) );
    assert(redis.existsKey("blogwebsite"));
    assert(redis.del("blogwebsite"));
    redis.close();
}

int main(int argc, char const *argv[])
{
    testRedisPool();
    return 0;
}
