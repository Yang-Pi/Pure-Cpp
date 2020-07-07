#include <iostream>
#include <stdexcept>

void task();

int main(int, char *[])
{
  try {
    task();
  }
  catch (const std::invalid_argument& err) {
    std::cerr << err.what();
    return 1;
  }
  catch (const std::exception& err) {
    std::cerr << err.what();
    return 2;
  }

  return 0;
}
