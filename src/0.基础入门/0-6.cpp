//
// Created by dqw on 2022/5/12.
//
/**
 * ··· io_service:io_service是线程安全的。几个线程可以同时调用io_service::run()。大多数情况下你可能在一个单线程函数中调用io_service::run()，
 *      这个函数必须等待所有异步操作完成之后才能继续执行。然而，事实上你可以在多个线程中调用io_service::run()。这会阻塞所有调用io_service::run()的线程。
 *      只要当中任何一个线程调用了io_service::run()，所有的回调都会同时被调用；这也就意味着，当你在一个线程中调用io_service::run()时，所有的回调都被调用了。
 * ··· socket:socket类不是线程安全的。所以，你要避免在某个线程里读一个socket时，同时在另外一个线程里面对其进行写入操作。（通常来说这种操作都是不推荐的，更别说Boost.Asio）。
 * ··· utility:就utility来说，因为它不是线程安全的，所以通常也不提倡在多个线程里面同时使用。里面的方法经常只是在很短的时间里面使用一下，然后就释放了。
 * **/

#include "boost/asio.hpp"
using boost::asio::ip::tcp;

void connect_handler(boost::system::error_code err){

}

void timeout_handler(boost::system::error_code err){

}

void run_service(boost::asio::io_context& ioContext){
    ioContext.run();
}
int main(){
    boost::asio::io_context ioContext;///所有的socket操作都由ioservice进行处理
    tcp::socket socket1(ioContext);
    tcp::socket socket2(ioContext);
    tcp::endpoint ep(tcp::v4(),8088);
//    boost::system::error_code err;
    socket1.async_connect(ep,connect_handler);///回调函数得有错误码
    socket2.async_connect(ep,connect_handler);

    boost::asio::deadline_timer t(ioContext,boost::posix_time::milliseconds(100));
    t.async_wait(timeout_handler);
    ////一个ioservice实例和一个处理线程的单线程例子
    ioContext.run();
//    for(int i=0;i<3;i++)std::thread(run_service, std::forward<boost::asio::io_context>(ioContext)).join();//todo:怎么构建多线程
}
