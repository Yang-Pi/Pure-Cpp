#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

struct token_t
{
  enum tokenType
  {
    WORD,
    NUMBER,
    PUNCT,
    DASH
  };

  std::string value;
  tokenType type;
};

#endif
