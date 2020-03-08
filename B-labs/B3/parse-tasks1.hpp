#include <iostream>
#include <string>
#include <cctype>

namespace details {
  int parseSmth(const std::string lineOrigin, std::string& resultLine,
      const std::string* samples, const size_t size);
  int parseNumber(const std::string lineOrigin, std::string& number);
  int parseName(const std::string lineOrigin, std::string& resultLine);
  int parseBookmark(const std::string lineOrigin, std::string& mark);
}
