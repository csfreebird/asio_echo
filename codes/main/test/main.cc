#include "test.h"
#include "util/endian.h"
#include "util/utf.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
  // TEST(3 > 2);
  char const * p = "一";
  cout << PrintStringAsBinaryString(p) << endl;
  string str = "一";
  cout << PrintStringAsBinaryString(str) << endl;
  cout << IsLittleEndian() << endl;
}
