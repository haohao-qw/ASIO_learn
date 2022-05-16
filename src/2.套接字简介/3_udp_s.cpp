//
// Created by dqw on 2022/5/16.
//

#include "boost/asio.hpp"
#include "array"
#include "iostream"
#include "ctime"
#include "string"
using boost::asio::ip::udp;

std::string make_datetime(){
    using namespace std;
    time_t now=time(0);
    return ctime(&now);
}

int main(){
    try {
        boost::asio::io_context io;
        udp::socket  sock(io,udp::endpoint(udp::v4(),8088));

        while(1){
            std::array<char,128>recv_buf;
            udp::endpoint remote_endpoint;
            sock.receive_from(boost::asio::buffer(recv_buf),remote_endpoint);

            std::string message=make_datetime();
            boost::system::error_code error;
            sock.send_to(boost::asio::buffer(message),remote_endpoint);
        }
    }catch (std::exception& e){
        std::cerr<<e.what()<<"\n";
    }
}