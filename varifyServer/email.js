/// 发送邮件的模块   
const nodeemailer = require('nodemailer')
const config_module = require('./config')

// 创建发送邮件的代理
let transport = nodeemailer.createTransport({
    host: 'smtp.126.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user, // 发送方邮件名
        pass: config_module.email_pass  // 发送方授权码
    }
});

// 发送邮件的函数
function SendMail(mailOptions_) {
    // transport.sendMail为异步函数,只能封装一个promise返回
    // 在调用出使用wait等待内部函数的完成
    return new Promise(function(resolve, reject){
        transport.sendMail(mailOptions_,function(error,info){
            if(error){
                console.log(error)
                reject(error)
            }else{
                console.log('邮件成功发送'+info.response)
                resolve(info.response)
            }
        })
    })
}

module.exports.SendMail = SendMail