#include <algorithm>
#include <iostream>
#include <sstream>

#include "token.hpp"
#include "token-reader.hpp"

void printUpdateText(std::vector<token_t>& vecText, const size_t outLineWidth)
{
  if (vecText.empty()) {
    return;
  }

  if (vecText.front().type == token_t::PUNCT || vecText.front().type == token_t::DASH) {
    throw std::invalid_argument("Can't begin with punctuation!\n");
  }

  //checking punctuation conditions
  for (auto iter = vecText.begin(); iter != vecText.end() - 1; ++iter) {
    if (iter->type == token_t::PUNCT) {
      if (iter->value == "," && (iter + 1)->type == token_t::DASH) {
        //comma can be before dash by task
        (iter + 1)->value.insert(0, " ");
      }
      else if ((iter + 1)->type == token_t::PUNCT || (iter + 1)->type == token_t::DASH) {
        throw std::invalid_argument("Two or more punctuation symbols nearby!\n");
      }
    }
  }

  //add space before words, numbers and "+"/"-"
  std::for_each(vecText.begin(), vecText.end(), [](token_t & token) {
        if (isalpha(token.value[0]) || isdigit(token.value[0]) || (token.value[0] == '+') || ((token.value[0] == '-'))) {
          token.value.insert(0, " ");
        }});

  size_t tmpWidth = 0;
  bool isBeginOfLine = true;

  for (auto iter = vecText.begin(); iter != vecText.end(); ++iter)
  {
    //delete waste space
    if (isBeginOfLine) {
      iter->value.erase(0, 1);
      isBeginOfLine = false;
    }

    //special situation: when punctuation mark or dash stays after word but they can't be written on one line
    if ((iter != vecText.end() - 1) && ((iter + 1)->type == token_t::DASH || (iter + 1)->type == token_t::PUNCT)) {
      const size_t widthNewLine = iter->value.size() + (iter + 1)->value.size() + tmpWidth;

      if (widthNewLine > outLineWidth) {
        std::cout << "\n" << iter->value.erase(0, 1);
        tmpWidth = iter->value.size();

        continue;
      }
    }

    const size_t tmpValueLenght = iter->value.size();

    if ((tmpWidth + tmpValueLenght) < outLineWidth) {
      std::cout << iter->value;
      tmpWidth += tmpValueLenght;

      isBeginOfLine = false;
    }
    else if ((tmpWidth + tmpValueLenght) == outLineWidth) {
      std::cout << iter->value << "\n";
      tmpWidth = 0;

      isBeginOfLine = true;
    }
    else if ((tmpWidth + tmpValueLenght) > outLineWidth) {
      std::cout << "\n" << iter->value.erase(0, 1);
      tmpWidth = tmpValueLenght - 1;

      isBeginOfLine = false;
    }
  }

  std::cout << "\n";
}
