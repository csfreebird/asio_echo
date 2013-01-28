#ifndef CORE_CONNECTION_H_
#define	CORE_CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <booster/log.h>
#include <boost/thread/thread.hpp>


using namespace boost::asio;
using ip::tcp;
using boost::system::error_code;

using namespace boost;
using namespace std;

template<class T>
class Connection: public boost::enable_shared_from_this<T> {
 public:

 Connection(io_service& s)
   : socket(s), strand_(s) {

  }

  ~Connection() {
  }

  // You must override it yourself
  // Default implementation closes the socket using shutdonw&cloes methods
  // You could override it if want change it
  // Or resue it with Connection::CloseSocket() format
  void CloseSocket() {
    try {
      socket.shutdown(tcp::socket::shutdown_both);
      socket.close();
    } catch (std::exception& e) {
      BOOSTER_INFO("Connection") << "thread id: " << this_thread::get_id() << e.what();
    }
  }
    
  // You must override it yourself
  virtual void StartJob() = 0;

  tcp::socket socket;
    
  // Strand to ensure the connection's handlers are not called concurrently.
  boost::asio::io_service::strand strand_;
};


#endif
