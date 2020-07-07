#include <iostream>
#include <exception>

void task1();
void task2();

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid number of arguments!\n";
    return 1;
  }

  try {
    int task = std::stoi(argv[1]);

    switch (task) {
    case 1:
      task1();
      break;

    case 2:
      task2();
      break;

    default:
      std::cerr << "Invalid task number!\n";
      return 1;
    }
  }
  catch (std::exception & err) {
    std::cerr << err.what() << '\n';
    return 2;
  }

  return 0;
}
