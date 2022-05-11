//
// Created by dqw on 2022/5/11.
//
#include "boost/asio.hpp"
using boost::asio::ip::tcp;

boost::asio::io_context io;
tcp::endpoint ep(tcp::v4(),8088);
tcp::socket sock(io);

void connect_handler(const boost::system::error_code &err){

}

int main(){
    sock.async_connect(ep,connect_handler);///回调得有error_code用于表示是否被调用成功
    io.run();
}