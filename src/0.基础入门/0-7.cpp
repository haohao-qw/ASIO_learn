//
// Created by dqw on 2022/5/12.
//
#include "boost/asio.hpp"
#include "iostream"
#include "thread"
using boost::asio::ip::tcp;
///todo:函数嵌套函数写法调用太多层 当数据量很大会不会崩？
/**
 * 同步客户端设计：
 * 1.使用用户名进行登录
 * 2.客户端主动连接服务端 服务端能够响应
 * 3.请求和回复都以"\n"结尾
 * 4.5s没有交互自动断开
 * ---能够截取所有连接客户端列表  随机ping
 * **/

const int max_msg=1024;

boost::asio::io_service ioser;
tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),8088);

class client{
private:
    std::string username;
    int already_read;
    char buff[max_msg];
    bool start;
    tcp::socket  socket;

public:
    client(std::string username_):username(username_), socket(ioser),start(true){};

    ///向服务端发送一个数据包
    void write_request(){
        std::string str="ping\n";
        boost::asio::write(socket,boost::asio::buffer(str.c_str(),str.size()));///发送数据
    }

    void on_login(){
        do_ask_clients();
    }

    void do_ask_clients(){
        std::string str="ask_client\n";
        boost::asio::write(socket,boost::asio::buffer(str.c_str(),str.size()));///发送数据
    }

    void on_ping(const std::string& msg){
        std::istringstream in(msg);
        std::string answer;
        in>>answer;///输出到anser
        if(answer=="client_list_changed")do_ask_clients();///这里采用流式输出 每次都会截取开空格 所以当有一次调用到就会执行新函数
    }

    void on_clients(const std::string& msg){
        std::string clients=msg.substr();
        std::cout<<username<<":  new client lists: "<<clients;
    }

    ///对接受到的数据进行解析
    void process_msg(){///对解析报文进行处理
        std::string msg(buff,already_read);///直接从buff中拿到数据
        if(msg.find("lonin")==0)on_login();///进行响应
        else if(msg.find("ping")==0)on_ping(msg);
        else if(msg.find("clients")==0)on_clients(msg);
        else std::cerr<<"invalid msg"<<msg<<std::endl;
    }

    size_t read_complete(const boost::system::error_code& err,size_t bytes){
        return 1;
    }

    ///读取上一次发送数据后的接收包
    void read_answer(){
        already_read=0;
        boost::asio::read(socket,boost::asio::buffer(buff,sizeof(buff)),
                          std::bind(&client::read_complete,this,std::placeholders::_1,std::placeholders::_2));
        process_msg();
    }

    void connect(tcp::endpoint ep){
        socket.connect(ep);
    }

    void loop(){
        std::string str="login"+username+"\n";
        boost::asio::write(socket,boost::asio::buffer(str.c_str(),str.size()));
        read_answer();
        while(start){
            write_request();
            read_answer();
            std::this_thread::sleep_for(std::chrono::seconds(std::rand()%7));///随机选择一个数
        }
    }
};

int main(){
    client c1("client_1");
    try{
        c1.connect(ep);
        c1.loop();
    }catch(boost::system::system_error& err){
        std::cout<<"client terminated\n";
    }
}
