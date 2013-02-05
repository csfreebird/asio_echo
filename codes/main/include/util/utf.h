#ifndef UTIL_UTF_H_
#define UTIL_UTF_H_

#include "util/endian.h"
#include <boost/locale/utf.hpp>

using namespace boost::locale::utf;

string PrintStringAsBinaryString(char const* p) {
  stringstream stream;
  for (size_t i = 0; i < strlen(p); ++i) {
    stream << PrintIntAsBinaryString(p[i]);
    stream << " ";
  }
  return stream.str();
}

string PrintStringAsBinaryString(string const& str) {
  stringstream stream;
  for (size_t i = 0; i < str.size(); ++i) {
    stream << PrintIntAsBinaryString(str[i]);
    stream << " ";
  }
  return stream.str();
}

// Convert the UTF-8 string that represent one single Unicode character in [start, end) to Unicode code point
code_point UTF8ToUnicode(char const* start, char const* end) {
  return utf_traits<char, sizeof(char)>::decode(start, end);
}


#endif

