#ifndef TEXT_GET_HPP
#define TEXT_GET_HPP

#include "token.hpp"

#include <string>
#include <vector>

const std::size_t WORD_MAX_LEN = 20;
const std::size_t DASH_MAX_LEN = 3;

class TokenReader
{
public:
  std::vector<token_t> readText();

private:
  void readWord(char);
  void readNumber(char);
  void readDash(char);

  std::vector<token_t> vecText_;
};

#endif
