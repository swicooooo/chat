let config_module = require('./config')
let Redis = require('ioredis')
require('core-js/stable/array/flat');   // 

// 创建Redis客户端实例
const RedisCli = new Redis({
    host: config_module.redis_host,
    port: config_module.redis_port,
    password: config_module.redis_passwd
})

// 监听错误消息
RedisCli.on("error",function(err) {
    console.log("RedisCli connect error: ",err)
    RedisCli.quit()
})

// 根据key获取value
async function get(key) {
    try{
        const result = await RedisCli.get(key)
        if(result === null) {
            console.log("RedisCli get key : ", key,",This key cannot be find...")
            return null
        }
        console.log("RedisCli get key : ", result,",Get key successfully!")
        return result
    }catch(error) {
        console.log("RedisCli get error: ", error)
        return null
    }
}

// 根据key查询value
async function exists(key) {
    try{
        const result = await RedisCli.exists(key)
        if(result === null) {
            console.log("RedisCli get key : ", key,",This key is null...")
            return null
        }
        console.log("RedisCli get key : ", result,",the key is exists!")
        return result
    }catch(error) {
        console.log("RedisCli exists error: ", error)
        return null
    }
}

// 设置key，value，expireTime
async function setKeyExpire(key,value,expireTime) {
    try{
        await RedisCli.set(key,value)
        await RedisCli.expire(key,expireTime)
        return true
    }catch(error) {
        console.log("RedisCli setKeyExpire error: ", error)
        return false
    }
}

// 退出函数
function quit() {
    RedisCli.quit()
}

module.exports = {get, exists, setKeyExpire, quit}