#ifndef UTIL_CONFIG_H_
#define UTIL_CONFIG_H_

#include <string>
using std::string;

class Configuration {

 public:
  Configuration(string const& path);

  string log_folder;

  string mongo_uri;

  int listen_port;
    
  int request_timeout;


};

#endif
