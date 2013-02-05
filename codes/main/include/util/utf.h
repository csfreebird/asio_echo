#ifndef UTIL_UTF_H_
#define UTIL_UTF_H_

#include "util/endian.h"

string PrintStringAsBinaryString(char const* p) {
  stringstream stream;
  for (size_t i = 0; i < strlen(p); ++i) {
    stream << PrintIntAsBinaryString(p[i]);
    stream << " ";
  }
  return stream.str();
}

#endif

