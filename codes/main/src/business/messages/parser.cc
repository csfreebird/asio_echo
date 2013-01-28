#include "business/messages/parser.h"

#include "util/endian.h"

uint16_t Parser::GetLength(vector<char> const& head) {
  return BigEndianBytesToInt<uint16_t>(head, 0, 2);
}

string Parser::GetString(vector<char> const& body, size_t start, size_t end) {
  return string(body.begin() + start, body.begin() + end);
}
