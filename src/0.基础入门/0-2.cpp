//
// Created by dqw on 2022/5/10.
//
#include "boost/asio.hpp"
#include "memory"
#include "functional"
#include "thread"
#include "iostream"
using boost::asio::ip::tcp;
using socket_ptr=std::shared_ptr<tcp::socket>;
///利用智能指针管理对象生命周期 但是多线程环境下智能指针也不是安全的 shared_ptr有两个阶段的赋值 如果在中间状态被抢占可能会发生ub

void client_session(socket_ptr ptr){
    while(true){
        char data[512];
        size_t len=ptr->read_some(boost::asio::buffer(data));
        if(len>0)write(*ptr,boost::asio::buffer(data,len));//todo：客户端关闭连接后error
    }
}
int main(){
    ///一个简单的服务端
    boost::asio::io_context ioContext;
    ///指定地址和端口
    tcp::endpoint ep(boost::asio::ip::tcp::v4(),8088);///监听地址和端口
    ///设置一个接收器 需要端口和ioservice
    tcp::acceptor acceptor(ioContext,ep);
    while(true){
        ///socket也需要一个iocontext
        socket_ptr socket(new tcp::socket(ioContext));
        ///将这个socket连接到创建的端口
        acceptor.accept(*socket);
        ///开启一个线程处理这个连接
        std::thread(std::bind(client_session,socket)).join();
    }
    return 0;
}

