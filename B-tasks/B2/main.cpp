#include <cstdlib>
#include <iostream>

void task1();
void task2();

int main(int argc, char * argv[])
{
  try {
    if (argc != 2) {
      std::cerr << "Invalid count of arguments!\n";
      return 1;
    }
    char* ptr = nullptr;
    size_t task = std::strtol(argv[1], &ptr, 10);
    if (*ptr != 0)  {
      std::cerr << "Invalid type of task argument!\n";
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
        std::cerr << "Invalid number of task argument!\n";
        return 1;
    }
  } catch (const std::exception & e) {
    std::cerr << e.what();
    return 2;
  }

  return 0;
}
