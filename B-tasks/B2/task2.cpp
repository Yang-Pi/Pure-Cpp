#include <list>
#include <iostream>

const int MIN = 1;
const int MAX = 20;
const size_t MAX_SIZE = 20;

void printList(std::list<int>::iterator, std::list<int>::iterator);

void task2()
{
  std::list<int> list(0);
  int iValue = 0;

  while (std::cin >> iValue) {
    if ( list.size() < MAX_SIZE) {
      if ( (iValue <= MAX) && (iValue >= MIN) ) {
        list.push_back(iValue);
      }
      else {
        throw std::invalid_argument("Value should be in range 1 to 20");
      }
    }
    else {
      throw std::invalid_argument("Too many numbers - no more than 20 ones");
    }
  }

  if ( !std::cin.eof() && std::cin.fail() ) {
    throw std::runtime_error("Input failed!\n");
  }

  if ( ! list.empty() ) {
    auto last = std::prev(list.end());
    printList(list.begin(), last);
  }
  else {
    return;
  }
}

void printList(std::list<int>::iterator first, std::list<int>::iterator last)
{
  if (first == last) {
    std::cout << *first << "\n";
    return;
  }

  if (first == std::prev(last)) {
    std::cout << *first << " " << *last << "\n";
    return;
  }

  std::cout << *first << " " << *last << " ";
  printList(++first, --last);
}
