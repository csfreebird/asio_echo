#ifndef CORE_SERVER_H_
#define CORE_SERVER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <booster/log.h>
#include <boost/thread/thread.hpp>
#include <vector>


using namespace std;
using namespace boost;
using boost::system::error_code;
using namespace boost::asio;
using ip::tcp;


// Crate a thread pool for io_service.
// Run the io_service to accept new incoming TCP connection and handle the I/O events
// You should provide your class as template argument here
// Your class must inherit from Connection class.
template<class T>
class Server {
 public:
  typedef T ClientType;
 Server(io_service& s, tcp::endpoint const& listen_endpoint, size_t threads_number)
   : io_(s),
    signals_(s),
    acceptor_(io_, listen_endpoint),
    thread_pool_size_(threads_number) {
      signals_.add(SIGINT);
      signals_.add(SIGTERM);
#if defined(SIGQUIT)
      signals_.add(SIGQUIT);
#endif
      signals_.async_wait(bind(&Server::Stop, this));
      shared_ptr<ClientType> c(new ClientType(io_));
          
      acceptor_.async_accept(c->socket, bind(&Server::AfterAccept, this, c, _1));
    }

  void AfterAccept(shared_ptr<ClientType>& c, error_code const& ec) {
    // Check whether the server was stopped by a signal before this completion
    // handler had a chance to run.
    if (!acceptor_.is_open()) {
      BOOSTER_INFO("Server") << "thread id: " << this_thread::get_id() << " acceptor is closed";
      return;
    }
        
    if (!ec) {
      c->StartJob();
      shared_ptr<ClientType> c2(new ClientType(io_));
      acceptor_.async_accept(c2->socket, bind(&Server::AfterAccept, this, c2, _1));
    }
  }

  // Create a thread pool for io_service
  // Launch io_service
  void Run() {
    // Create a pool of threads to run all of the io_services.
    vector<shared_ptr<thread> > threads;
    for (size_t i = 0; i < thread_pool_size_; ++i) {
      shared_ptr<thread> t(new thread(bind(&io_service::run, &io_)));
      threads.push_back(t);
    }

    // Wait for all threads in the pool to exit.
    for (std::size_t i = 0; i < threads.size(); ++i) {
      threads[i]->join();
    }
  }

 private:

  void Stop() {
    BOOSTER_INFO("Server") << "thread id: " << this_thread::get_id() << "stopping";
    acceptor_.close();
    io_.stop();
  }

 private:
  io_service& io_;
  boost::asio::signal_set signals_;
  tcp::acceptor acceptor_;
  size_t thread_pool_size_;
};

#endif
