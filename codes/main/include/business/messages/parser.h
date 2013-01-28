#ifndef BUSINESS_MESSAGES_PARSER_H_
#define BUSINESS_MESSAGES_PARSER_H_

#include <vector>
#include <string>
#include <boost/cstdint.hpp>

using namespace std;

class Parser {
 public:
  static uint16_t GetLength(vector<char> const& head);
  static string GetString(vector<char> const& body, size_t start, size_t end);
};

#endif
