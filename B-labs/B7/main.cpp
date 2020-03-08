#include <iostream>
#include <stdexcept>
#include <string>

void task1();
void task2();

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid count of arguments!\n";

    return 1;
  }

  char *checkPtr = nullptr;
  const int notation = 10;
  int nTask = std::strtol(argv[1], &checkPtr, notation);
  if (*checkPtr != '\0') {
    std::cerr << "Invalid format of task-argument!\n";

    return 1;
  }

  try {
    switch (nTask) {
      case 1 :
        task1();
        break;

      case 2 :
        task2();
        break;

      default :
        std::cerr << "Invalid value of task-argument!\n";
        
        return 1;
    }
  }
  catch (const std::invalid_argument& err) {
    std::cerr << err.what() << '\n';

    return 1;
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << '\n';

    return 2;
  }

  return 0;
}
