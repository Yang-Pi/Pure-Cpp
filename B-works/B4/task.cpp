#include <iostream>
#include <sstream>
#include <algorithm>

#include "dataStruct.hpp"
#include "taskFunctions.hpp"

void task()
{
  std::vector<DataStruct> vector;

  std::string line;

  while(std::getline(std::cin, line)) {
    if (std::cin.fail()) {
      throw std::ios_base::failure("Reading from stream has failed!\n");
    }
    DataStruct dataStruct = parse(line);

    vector.push_back(dataStruct);
  }

  std::sort(std::begin(vector), std::end(vector), compare);
  print(vector);
}
