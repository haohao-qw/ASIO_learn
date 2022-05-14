//
// Created by dqw on 2022/5/14.
//
#include "ctime"
#include "boost/asio.hpp"
#include "string"
#include "iostream"
using boost::asio::ip::tcp;

/**
 * 同步tcp时间服务器
 * 逻辑：接收后向这个socket发送本地时间就可以
 * 这里：string array似乎不用指定长度，char*需要给指针和长度
 */

std::string make_daytime(){
    using namespace std;
    time_t now=time(0);
    return ctime(&now);
}

int main(){
    try {
        boost::asio::io_context ioContext;
        tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 8088));

        while (true) {
            tcp::socket sock(ioContext);
            acceptor.accept(sock);
            std::string message = make_daytime();

            boost::system::error_code err;
            boost::asio::write(sock, boost::asio::buffer(message), err);
        }
    }catch (std::exception& e){
        std::cerr<<e.what()<<"\n";
    }
    return 0;
}
