//
// Created by dqw on 2022/5/16.
//


#include "boost/asio.hpp"
#include "array"
#include "iostream"
using boost::asio::ip::udp;

int main(){
    try{
        boost::asio::io_context io;

        udp::resolver resolver(io);
        udp::endpoint endpoint(udp::v4(),8088);

        udp::socket sock(io);
        sock.open(udp::v4());

        std::array<char,128>send_buf{{0}};
        sock.send_to(boost::asio::buffer(send_buf),endpoint);

        std::array<char,128>receive_buf{{0}};
        size_t len=sock.receive_from(boost::asio::buffer(receive_buf),endpoint);
        std::cout.write(receive_buf.data(),len);
    }catch (std::exception& e){
        std::cerr<<e.what()<<"\n";
    }
    return 0;
}