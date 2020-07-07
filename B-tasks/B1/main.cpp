#include <iostream>
#include <ctime>
#include <string>

#include "tasks.hpp"

int main(int argc, char * argv[])
{
  if ((argc <= 1) || (argc > 4)) {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  char * ptr = nullptr;
  int task = std::strtol(argv[1], &ptr, 10);
  if (*ptr) {
    std::cerr << "Invalid type of task-argument\n";
    return 1;
  }

  try {
    switch (task) {
      case 1: {
        if (argc != 3) {
          std::cerr << "Incorrect number of arguments\n";
          return 1;
        }
        task1(argv[2]);
        break;
      }
      case 2: {
        if (argc != 3) {
          std::cerr << "Incorrect number of arguments\n";
          return 1;
        }
        task2(argv[2]);
        break;
      }
      case 3: {
        if (argc != 2) {
          std::cerr << "Incorrect number of arguments\n";
          return 1;
        }
        task3();
        break;
      }
      case 4: {
        if (argc != 4) {
          std::cerr << "Incorrect number of arguments\n";
          return 1;
        }
        int vectorSize = std::strtol(argv[3], &ptr, 10);
        if (*ptr) {
          std::cerr << "Invalid type of size-argument\n";
          return 1;
        }

        srand(time(0));
        task4(argv[2], vectorSize);
        break;
      }
      default: {
        std::cerr << "Invalid number of task\n";
        return 1;
      }
    }
  } catch (const std::exception & e) {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
