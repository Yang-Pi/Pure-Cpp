#include <iostream>

void task1();
void task2();

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid count of arguments!\n";
    return 1;
  }

  try {
    char* checkPtr = nullptr;
    const int task = std::strtoll(argv[1], &checkPtr, 10);
    if (*checkPtr != '\0') {
      std::cerr << "Invalid type of task-argument!\n";
      return 1;
    }

    switch (task) {
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
  catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    return 2;
  }

  return 0;
}
