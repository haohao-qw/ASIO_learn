//
// Created by dqw on 2022/5/7.
//

#include "iostream"
#include "boost/asio.hpp"
#include "boost/asio/steady_timer.hpp"

int main(){
    boost::asio::io_service io;
    boost::asio::steady_timer t(io,std::chrono::seconds (5));
    t.wait();
    std::cout<<"wait ...\n";
    return 0;
}

