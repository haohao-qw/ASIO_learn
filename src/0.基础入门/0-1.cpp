//
// Created by dqw on 2022/5/10.
//

#define BOOST_ASIO_SEPARATE_COMPILATION
///添加这个宏在源文件中可以以源文件的方式编译asio

#include "asio.hpp"

int main(){
    ///基础的同步客户端例子
   ///首先需要一个ioservice实例 asio通过该实例同操作系统的输入输出服务进行交互
    asio::io_service ioService;
    ///通过endpoint创建要链接的地址和端口
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"),8088);
    ///其它构造方法：asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(),8088)
    ///创建socket 这个socket依赖于ioservice
    asio::ip::tcp::socket socket(ioService);
    ///使用socket的conect方法
    socket.connect(ep);
}