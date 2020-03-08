#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <set>
#include <sstream>

void task1()
{
  std::string line;
  std::set<std::string> wordsSet;

  while (std::getline(std::cin, line)) {
    std::stringstream stream(line);
    std::string word = "";

    while (stream >> word) {
      wordsSet.insert(word);
    }
  }

  std::ostream_iterator< std::string > out_it (std::cout,"\n");
  std::copy(wordsSet.begin(), wordsSet.end(), out_it);
}
