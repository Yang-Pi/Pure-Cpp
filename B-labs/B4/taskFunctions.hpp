#ifndef TASK_FUNCTIONS
#define TASK_FUNCTIONS

#include <vector>
#include "dataStruct.hpp"

const int ABSOLUTE_KEY_VALUE_LIMIT = 5;

DataStruct parse(std::string&);
int getKey(std::string&);
bool compare(const DataStruct&, const DataStruct&);
void print(const std::vector< DataStruct >&);

#endif //TASK_FUNCTIONS
