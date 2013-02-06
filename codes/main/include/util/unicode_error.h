#ifndef UTIL_UNICODE_ERROR_H_
#define UTIL_UNICODE_ERROR_H_

#include <stdexcept>
#include <string>

using std::logic_error;

class UnicodeError: public logic_error {

 public:
 UnicodeError(string const& msg):
  logic_error(msg) {
  }
};

#endif
