#include "parse-tasks1.hpp"

int details::parseSmth(const std::string lineOrigin, std::string& resultLine,
    const std::string* samples, const size_t size)
{
  std::string line = lineOrigin;
  if (!line.empty() && (size != 0)) {
    line = " " + line + " "; //condition of searching

    for (size_t i = 0; i < size; ++i) {
      std::string findingLine = " " + samples[i] + " ";
      size_t pos = line.find(findingLine);

      if (pos < line.size()) {
        resultLine = samples[i];
        return pos + samples[i].size();
      }
    }
  }

  return -1;
}

int details::parseNumber(const std::string lineOrigin, std::string& number)
{
  std::string line = lineOrigin;

  if (line.empty()) {
    return -1;
  }
  line = line.substr(0, line.find(' '));

  for (size_t i = 0; i < line.size(); ++i) {
    if (!std::isdigit(line[i]) && (line[i] != '+') && (line[i] != '-')) {
      return -1;
    }
  }

  number = line;
  return number.size();
}

int details::parseName(const std::string lineOrigin, std::string& name)
{
  std::string line = lineOrigin;

  if (line.empty()) {
    return -1;
  }

  if (line.front() != '\"') {
    return -1;
  }
  line.erase(line.begin());
  int counterDelChar = 1; //count all deleted symbols to value of return will be correct

  size_t i = 0;
  while ((i < line.size()) && (line[i] != '\"')) {
    if (line[i] == '\\') {
      if ((line[i + 1] == '\"') && ((i + 2) < line.size())) {
        line.erase(i, 1);
        ++counterDelChar;
      }
      else {
        return -1;
      }
    }
    ++i;
  }

  if (i == line.size()) {
    return -1;
  }
  line.erase(i); //delete last /"
  ++counterDelChar;

  if (line.empty()) {
    return -1;
  }

  name = line;
  return name.size() + counterDelChar;
}

int details::parseBookmark(const std::string lineOrigin, std::string& mark)
{
  std::string line = lineOrigin;

  if (line.empty()) {
    return -1;
  }
  line = line.substr(0, line.find(' '));

  for (size_t i = 0; i < line.size(); ++i) {
    if (!isalnum(line[i]) && (line[i] != '-')) {
      return -1;
    }
  }

  mark = line;
  return mark.size();
}
