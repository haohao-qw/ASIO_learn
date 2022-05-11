//
// Created by dqw on 2022/5/7.
//
#include "iostream"
#include "boost/asio.hpp"
#include "boost/system.hpp"
void print(const boost::system::error_code& /*e*/)
{
    std::cout << "Hello, world!" << std::endl;
}

int main(){
    boost::asio::io_service io;
    boost::asio::steady_timer t(io,boost::asio::chrono::seconds(2));
    t.async_wait(&print);
    std::cout<<"test start....\n";///这里不会被阻塞
    io.run();///到这里会阻塞等待print执行
    return 0;
}


