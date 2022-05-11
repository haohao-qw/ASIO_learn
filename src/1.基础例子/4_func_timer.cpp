#include "boost/asio.hpp"
#include "iostream"

class Printer{
private:
    boost::asio::steady_timer m_time;
    int count_;

public:
    explicit Printer(boost::asio::io_context& mcontext):count_(1),m_time(mcontext,std::chrono::seconds(1)){
        m_time.async_wait(std::bind(&Printer::print,this));
    };

    void print(){
        if(count_<5){
            std::cout<<count_<<"\n";
            ++count_;

            m_time.expires_at(m_time.expiry()+std::chrono::seconds(1));
            m_time.async_wait(std::bind(&Printer::print,this));
        }
    }

    ~Printer(){
        std::cout<<"finish....\n";
    }
};

int main(){
    boost::asio::io_context ioContext;
    Printer printer(ioContext);
    ioContext.run();
}