const grpc = require('@grpc/grpc-js')
const message_proto = require('./proto')

function main() {
    var client = new message_proto.VarifyService('localhost:50051',
                                         grpc.credentials.createInsecure());
    client.GetVarifyCode({email: '2186967306@qq.com'}, function(err, response) {
        console.log('recv:', response); // recv: { error: 0, email: '2186967306@qq.com', code: '' }
      })
}

main()
