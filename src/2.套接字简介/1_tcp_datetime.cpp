//
// Created by dqw on 2022/5/8.
//

#include "iostream"
#include "array"
#include "boost/asio.hpp"
using boost::asio::ip::tcp;


int main(){
    boost::asio::io_context io;
    tcp::resolver resolver(io);//解析
    ///tcp::resolver一般和tcp::resolver::query结合用，用来查询socket的相应信息 通过tcp::resolver很容易实现设置和查询

    tcp::resolver::results_type enpoints=resolver.resolve("www.baidu.com","80");///解析
    tcp::socket socket1(io);
    boost::asio::connect(socket1,enpoints);

    for(;;){
        std::array<char,128>buf;
        boost::system::error_code error;
        size_t len= socket1.read_some(boost::asio::buffer(buf),error);

        if(error==boost::asio::error::eof)break;
        else if(error) std::cout<<"error\n";
        std::cout.write(buf.data(),len);
    }

}

