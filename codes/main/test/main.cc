#include "test.h"
#include "util/endian.h"
#include "util/utf.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
  // TEST(3 > 2);
  char const * p = "一";
  cout << PrintStringAsBinaryString(p) << endl;
  string str = "一二三";
  cout << PrintStringAsBinaryString(str) << endl;

  string::iterator itor = str.begin();
  vector<code_point> points;
  UTF8ToUnicode(itor, str.end(), points);
  cout << "code point0: 0x" << std::hex << points[0] << " binary format:B" << PrintIntAsBinaryString(points[0]) << endl;
  cout << "code point1: 0x" << std::hex << points[1] << " binary format:B" << PrintIntAsBinaryString(points[1]) << endl;
  cout << "code point2: 0x" << std::hex << points[2] << " binary format:B" << PrintIntAsBinaryString(points[2]) << endl;
}
