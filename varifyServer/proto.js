const path  = require('path')
const grpc = require('@grpc/grpc-js')
const protoLoader = require('@grpc/proto-loader')

// 加载proto文件并获取具体消息
const PROTO_PATH = path.join(__dirname, 'message.proto')
const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
    keepCase : true,
    longs : String,
    enums : String,
    defaults : true,
    oneofs : true
})
const protoscriptor = grpc.loadPackageDefinition(packageDefinition)
const message_proto = protoscriptor.message

module.exports = message_proto  // 导出成员