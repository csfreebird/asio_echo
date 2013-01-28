#ifndef UTIL_CONFIG_ERROR_H_
#define UTIL_CONFIG_ERROR_H_

#include <stdexcept>
#include <string>

using std::logic_error;

class ConfigError: public logic_error {

 public:
 ConfigError(string const& msg):
  logic_error(msg){
  }
};

#endif
