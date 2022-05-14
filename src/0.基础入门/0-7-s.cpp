//
// Created by dqw on 2022/5/14.
//
#include "boost/asio.hpp"
#include "memory"
#include "sstream"
#include "thread"
#include "mutex"
#include "iostream"
using boost::asio::ip::tcp;
/**
 * 同步服务端
 * reactor模型
 * **/
boost::asio::io_context io;
const int max_=1024;
class server  :std::enable_shared_from_this<server>{
private:
    bool clients_changed;
    time_t last_time;
    std::string username_;
    tcp::socket socket;
    std::mutex mutex;
    using client_ptr=std::shared_ptr<server>;
    using array=std::vector<client_ptr>;
    array  clients;
    char buff[max_];
    int alreay_read;
public:
    server(std::string username): socket(io),username_(username){};

    void answer_to_client(){
        try{
            read_quest();
            process_request();
        }catch (boost::system::error_code&){
            stop();
        }
        if(time_out())stop();
    }

    void read_quest(){
        if(socket.available()){
            alreay_read+= socket.read_some(boost::asio::buffer(buff+alreay_read,max_-alreay_read));
        }
    }

    void stop(){
        boost::system::error_code err;
        socket.close(err);
    }

    bool time_out()const{
        time_t now;
        localtime(&now);
        long long ms=static_cast<long long>(now-last_time);
        return ms>5000;
    }

    void set_clients_changed(){
        clients_changed=true;
    }

    void on_login(const std::string& msg){
        std::istringstream in(msg);
        in>>username_;
        char* str="login ok\n";
        boost::asio::write(socket,boost::asio::buffer(str,strlen(str)));
    }

    void on_ping(){
        const char* cg=clients_changed ? "ping client_list_changed\n":"ping ok\n";

        write(socket,boost::asio::buffer(cg,strlen(cg)));
        clients_changed=false;
    }

    void on_clients(){
        std::string msg;
        {
            std::lock_guard<std::mutex>lock(mutex);
            for(auto it:clients){
                msg+=(*it).username_+" ";
            }
        }
        write(socket,boost::asio::buffer(msg.c_str(),msg.size()));
    }

    void process_request(){
        bool found_enter=std::find(buff,buff+alreay_read,'\n')<buff+alreay_read;///find stl查找函数
        if(!found_enter)return;

        localtime(&last_time);
        size_t pos=std::find(buff,buff+alreay_read,'\n')-buff;
        std::string msg(buff,pos);
        std::copy(buff+alreay_read,buff+max_,buff);//
        alreay_read-=pos+1;
        if(msg.find("login")==0)on_login(msg);
        else if(msg.find("ping")==0)on_ping();
        else if(msg.find("ask_clients")==0)on_clients();
        else std::cerr<<"invaild msg"<<msg<<std::endl;
    }

    void accept_thread(){
        tcp::acceptor acceptor(io,tcp::endpoint(tcp::v4(),8088));
        while(true){
            client_ptr ptr(new server("server"));
            acceptor.accept(ptr->socket);
            {
                std::lock_guard<std::mutex> lock(mutex);
                clients.push_back(ptr);
            }
        }
    }

    void handle_clients_thread(){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            {
                std::lock_guard<std::mutex> lock(mutex);
                for(auto it:clients){
                    (*it).answer_to_client();
                }
                ///删除超时的客户端
                clients.erase(std::remove_if(clients.begin(),clients.end(),
                                             std::bind(&server::time_out,this)));
            }
        }
    }
};

int main(){

}


