#include <iostream>
#include <stdexcept>

#include "token-reader.hpp"

const size_t MIN_WIDTH = 25;
const size_t DEFAULT_WIDTH = 40;

void printUpdateText(std::vector<token_t>&, const size_t);

int main(int argc, char * argv[])
{
  try {
    if ((argc != 1) && (argc != 3)) {
      std::cerr << "Invalid number of arguments!\n";

      return 1;
    }

    size_t width = DEFAULT_WIDTH;

    if (argc == 3) {
      width = std::stoi(argv[2]);

      if ((std::string(argv[1]) != "--line-width") || (width < MIN_WIDTH)) {
        std::cerr << "Invalid arguments!\n";

        return 1;
      }
    }

    TokenReader text;
    std::vector<token_t> textUpdt = text.readText();

    printUpdateText(textUpdt, width);
  }
  catch (const std::exception & err) {
    std::cerr << err.what();

    return 2;
  }

  return 0;
}
