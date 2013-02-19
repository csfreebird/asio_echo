#ifndef UTIL_ENDIAN_H_
#define UTIL_ENDIAN_H_

#include <cstring>
#include <boost/cstdint.hpp>
#include <vector>
#include <sstream>
//#include <endian.h>

using namespace std;

// Get the bit value specified by the index
// index starts with 0
template<class T>
int Bit_Value(T value, uint8_t index) {
  return (value & (1 << index)) == 0 ? 0 : 1;
}

// T must be one of integer type
template<class T>
string PrintIntAsBinaryString(T v) {
  stringstream stream;
  int i = sizeof(T) * 8 - 1;
  while (i >= 0) {
    stream << Bit_Value(v, i);
    --i;
  }
    
  return stream.str();
}

static union {
  char c[4];
  unsigned char l;
} endian_test = {{'l','?','?','b'}};

#define IsLittleEndian() (endian_test.l == 'l')

// Convert the following integer values to big-endian if necessary
template<class T>
T Int16ToBigEndian(T value) {
  if (IsLittleEndian()) {
    uint8_t* p = reinterpret_cast<uint8_t*> (&value);
    T v1 = static_cast<T> (p[0]);
    T v2 = static_cast<T> (p[1]);
    return (v1 << 8) | v2;
  } else {
    return value;
  }
}

template<class T>
T Int32ToBigEndian(T value) {
  if (IsLittleEndian()) {
    uint8_t* p = reinterpret_cast<uint8_t*> (&value);
    T v1 = static_cast<T> (p[0]);
    T v2 = static_cast<T> (p[1]);
    T v3 = static_cast<T> (p[2]);
    T v4 = static_cast<T> (p[3]);
    return (v1 << 24) | (v2 << 16) << (v3 << 8) | v4;
  } else {
    return value;
  }
}


// The following functions convert the byte arrays 
// that has big-endian into integers on local platform

// The size of value should be 2
template<class T>
T BigEndianBytesToInt16(vector<char> const& value) {
  if (IsLittleEndian()) {
    T h = static_cast<T> (value[0]);
    T l = static_cast<T> (value[1]);
    return (h << 8) | l;
  } else {
    T tmp = 0;
    memcpy(&tmp, &value[0], 2);
    return tmp;
  }
}

/*
template<class T>
T BigEndianBytesToInt32(char value[4]) {
  if (IsLittleEndian2()) {
    union {
      uint32_t u32;
      uint8_t arr[4];
    } x;
    x.arr[0] = value[0];
    x.arr[1] = value[1];
    x.arr[2] = value[2];
    x.arr[3] = value[3];
    return be32toh(x.u32);
  } else {
    T tmp = 0;
    memcpy(&tmp, &value[0], 4);
    return tmp;
  }
}
*/

/*
template<class T>
T BigEndianBytesToInt32(char value[4]) {
  union {
    uint32_t u32;
    uint8_t arr[4];
  } x;
  if (IsLittleEndian2()) {
    T a = static_cast<T>(value[0]);
    T b = static_cast<T>(value[1]);
    T c = static_cast<T>(value[2]);
    T d = static_cast<T>(value[3]);
    return (a << 24) | ((b & 0xff) << 16) | ((c & 0xff) << 8) | (d & 0xff);
  } else {
    memcpy(&x.arr[0], &value[0], 4);
    return x.u32;
  }
}
*/

template<class T>
T BigEndianBytesToInt(vector<char> value, size_t first, size_t last) {
  if (IsLittleEndian()) {
    T result;
    for (size_t i = first; i < last; ++i) {
      size_t offset = (last - i - 1) * 8;
      T cur = static_cast<T>(static_cast<uint8_t>(value[i]));
      if (i == first) {
	result = cur << offset;
      } else if (i == first -1) {
	result = result | cur;
      } else {
	result = result | cur << offset;
      }
    }
    return result;
  } else {
    T tmp = 0;
    memcpy(&tmp, &value[0], 4);
    return tmp;
  }
}

#endif
