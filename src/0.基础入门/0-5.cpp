//
// Created by dqw on 2022/5/11.
//

#include "boost/asio.hpp"
#include "iostream"
#include "memory"
using boost::asio::ip::tcp;
/***
 * 错误处理
 */


using sockptr=std::shared_ptr<tcp::socket>;
boost::asio::io_service io;
tcp::endpoint ep(tcp::v4(),8088);
tcp::acceptor acc(io,ep);

void start_accept(sockptr sock);

void handle_acceot(sockptr ptr,const boost::system::error_code &err){
    if(err)return;
    sockptr mh_sock(new tcp::socket(io));
    std::cout<<"ok\n";
    start_accept(mh_sock);
}
///Boost.Asio允许同时使用异常处理或者错误代码，所有的异步函数都有抛出错误和返回错误码两种方式的重载。
/// 当函数抛出错误时，它通常抛出boost::system::system_error的错误。
/**
 * 比如：sock.connect(ep)  抛出错误
 *      sock.connect(ep,error) 返回错误码
 * **/
void start_accept(sockptr sock){
    try {
        ///异步函数不抛出异常 一般通过try catch方式进行处理
        acc.async_accept(*sock, std::bind(&handle_acceot, sock, std::placeholders::_1));
    }catch (boost::system::system_error e){
        ///使用错误码可以很好的检测连接是如何关闭的
        std::cout<<"error:"<<e.code()<<"\n";
    }
}

int main() {
    sockptr ptr(new tcp::socket(io));
    start_accept(ptr);
    io.run();
}

