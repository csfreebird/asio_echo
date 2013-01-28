#include "business/client.h"
#include <boost/bind.hpp>
#include "util/endian.h"
#include <booster/log.h>
#include "util/my_app.h"
#include "business/messages/parser.h"

using namespace boost;

Client::Client(io_service& s):
  Connection(s), length_buffer_(2, 0), string_buffer_(200, 0), wait_request_timer_(s) {
}

void Client::StartJob() {
  BOOSTER_INFO("Client") << "thread id: " << this_thread::get_id() << " start job";
  async_read(socket, buffer(length_buffer_),
	     strand_.wrap(bind(&Client::AfterReadLength, shared_from_this(), _1)));
  wait_request_timer_.expires_from_now(boost::posix_time::seconds(AppHolder::Instance().config().request_timeout));
  wait_request_timer_.async_wait(strand_.wrap(bind(&Client::AfterTimeout, shared_from_this(), _1)));
}

void Client::AfterTimeout(error_code const& ec) {
  if (ec.value() == boost::asio::error::operation_aborted) {
    BOOSTER_INFO("AfterTimeout") << "AfterTimeout was canceled";
    return;
  }

  if (wait_request_timer_.expires_at() <= deadline_timer::traits_type::now()) {
    BOOSTER_ERROR("AfterTimeout") << "close the socket because the request didn't arrive in specified time";
    wait_request_timer_.cancel();
    CloseSocket();
  }
}

void Client::CloseSocket() {
  Connection::CloseSocket();
}

Client::~Client() {
  BOOSTER_INFO("Client") << "thread id: " << this_thread::get_id() << " ~client";
  CloseSocket();
}

void Client::AfterReadLength(error_code const& ec) {
  BOOSTER_INFO("AfterReadLength") << "thread id: " << this_thread::get_id() << " enter AfterReadLength";
  if (ec) {
    BOOSTER_INFO("AfterReadLength") << "thread id: " << this_thread::get_id() << ec.message();
    return;
  }
  
  uint16_t length = Parser::GetLength(length_buffer_);
  if (length > 0 && length < 201) {
    // stop the timer
    wait_request_timer_.cancel();

    BOOSTER_INFO("AfterReadLength") << "thread id: " << this_thread::get_id() << " length:" << length;
    string_buffer_.assign(200, 0);
    async_read(socket, buffer(string_buffer_, length),
    	       strand_.wrap(bind(&Client::AfterReadString, shared_from_this(), _1, length)));
  } else {
    BOOSTER_INFO("AfterReadLength") << "thread id: " << this_thread::get_id() << " wrong size received, length:" << length;
    CloseSocket();
  }
}


void Client::AfterReadString(error_code const& ec, uint16_t size) {
  if (ec) {
    BOOSTER_INFO("AfterReadString") << "thread id: " << this_thread::get_id() << " error:" << ec.message() ;
    return;
  }

  string message = Parser::GetString(string_buffer_, 0, size);
  BOOSTER_INFO("AfterReadString") << "thread id: " << this_thread::get_id() << " message:" << message;

  vector<const_buffer> buffers;
  buffers.push_back(buffer(length_buffer_));
  buffers.push_back(buffer(string_buffer_));
  async_write(socket, buffers,
	      strand_.wrap(bind(&Client::AfterWriteResponse, shared_from_this(), _1)));
}

void Client::AfterWriteResponse(error_code const& ec) {
  if (ec) {
    BOOSTER_INFO("AfterWriteResponse") << "thread id: " << this_thread::get_id() << " error:" << ec.message() ;
    return;
  }
  BOOSTER_INFO("AfterReadString") << "thread id: " << this_thread::get_id() << " write response successfully";
}
