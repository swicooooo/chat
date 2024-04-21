const grpc = require('@grpc/grpc-js')
const message_proto = require('./proto')
const const_module = require('./const')
const { v4: uuidv4} = require('uuid')
const emailModule = require('./email')
const config_module = require('./config')
const redis_module = require('./redis')

/// grpc响应获取验证码的服务
/// call: grpc请求
/// callback： grpc回调
async function GetVarifyCode(call, callback) {
    console.log("email is ",call.request.email)
    try{
        // 查询redis,如果过期则重新生成(600s)，否则用redis中的数据发送邮件
        // 在这里必须要await，因为ioredis提供的是异步方法，这样才能获得promise包裹的返回结果
        let query_res = await redis_module.get(const_module.code_prefix+call.request.email)
        console.log("query is ",query_res)

        let uniqueId = query_res
        if(query_res == null) {
            uniqueId = uuidv4()
            if(uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0,4)
            }
            let res = await redis_module.setKeyExpire(const_module.code_prefix+call.request.email, uniqueId,600)
            // redis设置出错
            if(!res) {
                callback(null, {
                    email: call.request.email,
                    error: const_module.RedisErr
                })
                return
            }
        }
        console.log("uniqueId is ",uniqueId)
        let text_str = '您的验证码为'+ uniqueId +'请三分钟内完成注册'
        
        // 发送邮件
        let mailOptions = {
            from: config_module.email_user,
            to: call.request.email,
            subject: '验证码',
            text: text_str
        }
        let send_res = await emailModule.SendMail(mailOptions)
        console.log("send res is ",send_res)

        // 调用回调，向grpc客户端发送消息
        callback(null, {
            email: call.request.email,
            error: const_module.Success
        })
    }catch(error){
        console.log("catch error is ", error)

        callback(null, { email:  call.request.email,
            error:const_module.Errors.Exception
        }); 
    }
}

function main() {
    var server = new grpc.Server()
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode});
    server.bindAsync('0.0.0.0:50051',grpc.ServerCredentials.createInsecure(),()=>{
        // server.start()
        console.log('varify server started')  
    })
}

main()