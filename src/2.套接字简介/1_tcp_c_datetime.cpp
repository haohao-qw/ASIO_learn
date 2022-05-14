//
// Created by dqw on 2022/5/8.
//
#include "iostream"
#include "boost/asio.hpp"
#include "array"

using boost::asio::ip::tcp;
/**
 * 同步tcp时间客户端
 * todo:这个例子文档中采用服务器名称解析完成 这里直接用ip连接了，改进为用服务器名称解析
 * 1-s提供了一个时间服务器，发送内容是本地时间，这里用array接收数据后打印显示 注意这里用error中eof进行结尾处理 同socke编程 否则异常
 * **/
int main() {
    try{
        boost::asio::io_context ioContext;

        tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"),8088);

        tcp::socket socket(ioContext);

        socket.connect(endpoint);

        while (true) {
            std::array<char, 128> buf;
            boost::system::error_code err;
            size_t len = socket.read_some(boost::asio::buffer(buf), err);

            if (err == boost::asio::error::eof) {///
                break;
            } else if (err) throw boost::system::system_error(err);

            std::cout.write(buf.data(), len);
        }
    }catch (std::exception& e){
           std::cerr<<e.what()<<"\n";
    }
}
