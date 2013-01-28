#ifndef BUSINESS_CLIENT_H_
#define BUSINESS_CLIENT_H_

#include "core/connection.h"
#include <vector>

using namespace std;

class Client: public Connection<Client> {
 public:
  Client(io_service& s);

  ~Client();

  void StartJob();

  void CloseSocket();

  void AfterReadLength(error_code const& ec);

  void AfterReadString(error_code const& ec, uint16_t size);

  void AfterTimeout(error_code const& ec);

  void AfterWriteResponse(error_code const& ec);

 private:
  vector<char> length_buffer_;
  vector<char> string_buffer_;
  deadline_timer wait_request_timer_;
};

#endif
