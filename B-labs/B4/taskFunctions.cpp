#include <stdexcept>
#include <iostream>
#include <string>
#include <boost/algorithm/string/trim.hpp>

#include "taskFunctions.hpp"

DataStruct parse(std::string& line)
{
  if (line.empty()) {
    throw std::invalid_argument("You've just sent empty line to parse function!\n");
  }
  int key1 = getKey(line);
  int key2 = getKey(line);

  if (line.empty()) {
    throw std::invalid_argument("The line doesn't contain the last paramert!\n");
  }

  return {key1, key2, line};
}

int getKey(std::string& line)
{
  std::size_t commaPos = line.find_first_of(',');
  if (commaPos == std::string::npos) {
    throw std::invalid_argument("Invalid view of line!\n");
  }

  std::string sKey = line.substr(0, commaPos);
  //try to find number before comma
  char * ptr = nullptr;
  int iKey = std::strtol(sKey.data(), &ptr, 10);
  if (*ptr) {
    throw std::invalid_argument("Wrong format of key!\n");
  }
  //analize finded number
  if (std::abs(iKey) > ABSOLUTE_KEY_VALUE_LIMIT) {
    throw std::out_of_range("Value of key is out of range!\n");
  }
  line.erase(0, commaPos + 1);
  boost::algorithm::trim_left(line);

  return iKey;
}

bool compare(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 < rhs.key1) {
    return true;
  }

  if (lhs.key1 == rhs.key1) {
    if (lhs.key2 < rhs.key2) {
      return true;
    }

    if ((lhs.key2 == rhs.key2) && (lhs.str.length() < rhs.str.length())) {
      return true;
    }
  }

  return false;
}

void print(const std::vector< DataStruct >& vector)
{
  for (DataStruct dataStruct : vector) {
    std::cout << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << "\n";
  }
}
