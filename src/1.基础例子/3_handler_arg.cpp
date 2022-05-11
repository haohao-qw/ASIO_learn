//
// Created by dqw on 2022/5/7.
//
#include "boost/asio.hpp"
#include "iostream"
#include "boost/bind/bind.hpp"

void print(const boost::system::error_code&,boost::asio::steady_timer* t,int *count){
    if(*count<5) {
        std::cout << *count << "\n";
        ++(*count);
        //调整时间：从上一个到期时间移动一秒 大概是时间过期的话异步操作就会结束 因此需要不断更新时间保证异步进行
        t->expires_at(t->expiry()+boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(print,boost::asio::placeholders::error,t,count));
    }
}
///异步定时器
int main(){
    boost::asio::io_context io;
    int count=1;
    boost::asio::steady_timer t(io,boost::asio::chrono::seconds(1));
    t.async_wait(boost::bind(print,boost::asio::placeholders::error,&t,&count));
    io.run();
    return 0;
}

