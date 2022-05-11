//
// Created by dqw on 2022/5/8.
//

#include "thread"
#include "boost/asio.hpp"
#include "iostream"
#include "functional"

class printer{
private:
    /// https://www.cnblogs.com/my_life/articles/5331789.html
//    Boost Asio将数据传输分为两个独立的步骤：
//    采用异步任务的方式开始数据传输。
//    将传输结果回调通知调用端
//基于Boost.Asio来提高程序的可扩展性推荐的方法是：采用单个I/O service多次调用run()方法
    boost::asio::strand<boost::asio::io_context::executor_type>strand_;///strand定义了事件处理程序的严格顺序调用 能够保证线程安全
    boost::asio::steady_timer timer1;
    boost::asio::steady_timer timer2;
    int count_=0;
public:
    printer(boost::asio::io_context& ioContext):strand_(boost::asio::make_strand(ioContext))
            ,timer1(ioContext,std::chrono::seconds(1)),timer2(ioContext,std::chrono::seconds(1)),count_(0){
        timer1.async_wait(std::bind(&printer::print1,this));
        timer2.async_wait(std::bind(&printer::print2,this));
    }

    void print1(){
        std::cout<<"count:"<<count_<<"\n";
        if(count_<10){
            ++count_;
            timer1.expires_at(timer1.expiry()+std::chrono::seconds(1));
            timer1.async_wait(std::bind(&printer::print1,this));
        }
    }

    void print2(){
        std::cout<<"count:"<<count_<<"\n";
        if(count_<10){
            ++count_;
            timer2.expires_at(timer2.expiry()+std::chrono::seconds(1));
            timer2.async_wait(std::bind(&printer::print2,this));
        }
    }

    ~printer(){
        std::cout<<"finsh..\n";
    }
};

int main(){
    boost::asio::io_context ioContext;
    printer p(ioContext);
    ioContext.run();
}
