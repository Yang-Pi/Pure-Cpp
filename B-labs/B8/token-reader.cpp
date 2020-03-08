#include <algorithm>
#include <iostream>
#include <sstream>

#include "token.hpp"
#include "token-reader.hpp"

std::vector<token_t> TokenReader::readText()
{
  while (std::cin) {
    std::cin >> std::ws;
    char firstChar = static_cast<char>(std::cin.get());
    char secondChar = static_cast<char>(std::cin.peek());

    //if the char is a letter
    if (std::isalpha(firstChar)) {
      readWord(firstChar);
    }
    //if the char is a number
    else if (std::isdigit(firstChar) || ((firstChar == '+' || firstChar == '-') && std::isdigit(secondChar))) {
      readNumber(firstChar);
    }
    //if it is a punctuation mark
    else if (std::ispunct(firstChar)) {
      if (firstChar == '-') {
        readDash(firstChar);
      }
      else {
        std::string sChar(1, firstChar);
        vecText_.push_back(token_t{sChar, token_t::PUNCT});
      }
    }
  }

  return vecText_;
}

void TokenReader::readWord(char letter)
{
  std::string word(1, letter);

  while (std::isalpha(std::cin.peek()) || std::cin.peek() == '-') {
    char ch = static_cast<char>(std::cin.get());

    if (ch == '-' && std::cin.peek() == '-') {
      throw std::invalid_argument("Too long hyphen in the word!\n");
    }

    word.push_back(ch);
  }

  if (word.length() > WORD_MAX_LEN) {
    throw std::invalid_argument("Length of the word more than 20!\n");
  }

  vecText_.push_back(token_t{word, token_t::WORD});
}

void TokenReader::readNumber(char numeral)
{
  std::string number(1, numeral);

  int countDots = 0;

  while (std::isdigit(std::cin.peek()) || std::cin.peek() == '.') {
    char ch = static_cast<char>(std::cin.get());

    if (ch == '.') {
      ++countDots;
      if (countDots == 2) {
        break;
      }
    }

    number.push_back(ch);
  }

  if (number.length() > WORD_MAX_LEN) {
    throw std::invalid_argument("Length of the number more than 20!\n");
  }

  vecText_.push_back(token_t{number, token_t::NUMBER});
}

void TokenReader::readDash(char hyphen)
{
  std::string dash(1, hyphen);

  while (std::cin.peek() == '-') {
    dash.push_back(static_cast<char>(std::cin.get()));
  }

  if (dash.length() != DASH_MAX_LEN) {
    throw std::invalid_argument("Dash should include only 3 hyphen!\n");
  }

  vecText_.push_back(token_t{dash, token_t::DASH});
}
