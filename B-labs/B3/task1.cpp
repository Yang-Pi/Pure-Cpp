#include <iostream>
#include <string>
#include <boost/algorithm/string/trim.hpp>

#include "phone-book-UI.hpp"
#include "parse-tasks1.hpp"

using namespace details;

const int N_COMMANDS = 6;
const std::string COMMANDS[N_COMMANDS] = {
    "add", "store", "insert", "delete", "show", "move"};

void handleLine(std::string& line, const int pos)
{
  if (pos < 0) {
    return;
  }
  line.erase(0, pos);
  boost::algorithm::trim_left(line);
}

void task1()
{
  PhoneBookUI phoneBook;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (std::cin.fail()) {
      throw std::runtime_error("Input failed!\n");
    }

    std::string command = "";
    int pos = parseSmth(line, command, COMMANDS, N_COMMANDS);

    if (pos != -1) {
      if (command == "add") {
        handleLine(line, pos);

        std::string number = "";
        int posNumber = parseNumber(line, number);
        handleLine(line, posNumber);

        std::string name = "";
        int posName = parseName(line, name);
        handleLine(line, posName);

        if ((posNumber != -1) && (posName != -1)) {
          phoneBook.add({number, name});
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }

        continue;
      }

      if (command == "store") {
        handleLine(line, pos);

        std::string mark1;
        int posMark1 = parseBookmark(line, mark1);
        handleLine(line, posMark1);

        std::string mark2;
        int posMark2 = parseBookmark(line, mark2);
        handleLine(line, posMark2);

        if ((posMark1 != -1) && (posMark2 != -1)) {
          phoneBook.store(mark1, mark2);
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }

        continue;
      }

      if (command == "insert") {
        handleLine(line, pos);

        const int n = 2;
        const std::string arr[n] = {"before", "after"};

        std::string insertWhere = "";
        int posInsert = parseSmth(line, insertWhere, arr, n);
        handleLine(line, posInsert);

        std::string mark = "";
        int posMark = parseBookmark(line, mark);
        handleLine(line, posMark);

        std::string number = "";
        int posNumber = parseNumber(line, number);
        handleLine(line, posNumber);

        std::string name = "";
        int posName = parseName(line, name);
        handleLine(line, posName);

        if ((posInsert != -1) && (posMark != -1) && (posNumber != -1) && (posName != -1)) {
          if (insertWhere == "after") {
            phoneBook.insert(true, mark, {number, name});
          }
          else {
            phoneBook.insert(false, mark, {number, name});
          }
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }

        continue;
      }

      if (command == "delete") {
        handleLine(line, pos);

        std::string mark = "";
        int posMark = parseBookmark(line, mark);
        handleLine(line, posMark);

        if (posMark != -1) {
          phoneBook.remove(mark);
        }
        else {
          std::cout << "<INVALID ARGUMENTS OF COMMAND>\n";
        }

        continue;
      }

      if (command == "show") {
        handleLine(line, pos);

        std::string mark = "";
        int posMark = parseBookmark(line, mark);
        handleLine(line, posMark);

        if (posMark != -1) {
          std::cout << phoneBook.show(mark) << '\n';
        }
        else {
          std::cout << "<INVALID ARGUMENTS OF COMMAND>\n";
        }

        continue;
      }

      if (command == "move") {
        handleLine(line, pos);

        std::string mark = "";
        int posMark = parseBookmark(line, mark);
        handleLine(line, posMark);

        std::string steps = "";
        int posSteps = parseNumber(line, steps);

        if ((posMark != -1) && (posSteps != -1)) {
          char* checkPtr = nullptr;
          const int iSteps = std::strtoll(steps.data(), &checkPtr, 10);

          if (*checkPtr == '\0') {
            phoneBook.move(mark, iSteps);
          }
        }
        else if (posSteps == -1) {
          const int n = 2;
          const std::string arr[2] = {"first", "last"};
          posSteps = parseSmth(line, steps, arr, n);

          if (posSteps != -1) {
            phoneBook.move(mark, steps);
          }
          else {
            std::cout << "<INVALID STEP>\n";
          }
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
        handleLine(line, posSteps);

        continue;
      }

    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
