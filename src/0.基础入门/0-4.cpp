//
// Created by dqw on 2022/5/11.
//
#include "boost/asio.hpp"
#include "iostream"
#include "memory"
using boost::asio::ip::tcp;

/*
 * 异步服务器
 * */

using sockptr=std::shared_ptr<tcp::socket>;
boost::asio::io_context io;
tcp::endpoint ep(tcp::v4(),8088);
tcp::acceptor acc(io,ep);

void start_accept(sockptr sock);

///似乎为了保证异步 asio很多写法都是这种 嵌套回调
void handle_acceot(sockptr ptr,const boost::system::error_code &err){
    if(err)return;
    sockptr mh_sock(new tcp::socket(io));
    std::cout<<"ok\n";
    start_accept(mh_sock);
}

void start_accept(sockptr sock){
    acc.async_accept(*sock,std::bind(&handle_acceot,sock,std::placeholders::_1));
}

int main() {
    sockptr ptr(new tcp::socket(io));
    start_accept(ptr);
    io.run();
}
