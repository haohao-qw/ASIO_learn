//
// Created by dqw on 2022/5/12.
//
#include "boost/asio.hpp"
#include "iostream"

///     ***********客户端******************
///客户端可以ping ping时服务端返回ping ok或者ping client_list_chaned
////每个客户端登录六个用户连接  每个客户端连接随机ping服务器 随机7秒

using boost::asio::ip::tcp;
tcp::endpoint ep(tcp::v4(),8088);
boost::asio::io_context ioContext;



class client{
private:
    std::string username;
    enum {max_msg=1024};
    int already_read;
    char buff[max_msg];
    bool started;
    tcp::socket sock;

public:
    client(const std::string& name):username(name), sock(ioContext),started(true){};

    void write_request(){
        boost::asio::write("ping\n");
    }

    size_t read_complete(const boost::system::error_code& err,size_t butes){

    }

    void process_msg(){
        std::string msg(buff,already_read);

    }

    void read_answer(){
        already_read=0;
        boost::asio::read(sock,boost::asio::buffer(buff),std::bind(&read_complete,this,std::placeholders::_1,std::placeholders::_2))
        process_msg();
    }

    void connect(tcp::endpoint ep){
        sock.connect(ep);
    }
};
