#include <iostream>
#include <cstring>
#include <boost/algorithm/string/trim.hpp>

#include "queue-with-priority.hpp"

const int nCommands = 3;
const std::string COMMANDS[nCommands] = {"add", "get", "accelerate"};

const int nPriorities = 3;
const std::string PRIORITIES[nPriorities] = {"high", "normal", "low"};

void add(std::string, QueueWithPriority<std::string> &);
size_t parse(std::string, std::string&, const std::string*, const size_t size);

void task1()
{
  std::string line;
  QueueWithPriority<std::string> queue;

  while (std::getline(std::cin, line)) {
    if ( std::cin.fail() ) {
      throw std::runtime_error("Input failed!\n");
    }

    std::string command;
    int pos = parse(line, command, COMMANDS, nCommands);

    if (pos != -1) {
      if (strcmp(command.data(), "add") == 0) {
        line.erase(0, 3);
        add(line, queue);
        continue;
      }

      if (strcmp(command.data(), "get") == 0) {
        std::string elem;
        bool get = queue.getElement(elem);
        if (get) {
          std::cout << elem << "\n";
        }
        else {
          std::cout << "<EMPTY>\n";
        }
        continue;
      }

      if (strcmp(command.data(), "accelerate") == 0) {
        queue.accelerate();
      }
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

size_t parse(std::string line, std::string& resultLine, const std::string* samples, const size_t size)
{
  if ( !line.empty() && (size != 0) ) {
    line = " " + line + " "; //condition of searching
    for (size_t i = 0; i < size; ++i) {
      std::string findingLine = " " + samples[i] + " ";
      size_t pos = line.find(findingLine);

      if ( pos < line.length() ) {
        resultLine = samples[i];
        return pos;
      }
    }
  }

  return -1;
}

void add(std::string line, QueueWithPriority<std::string> & queue)
{
  std::string priorityStr;
  int pos = parse(line, priorityStr, PRIORITIES, nPriorities);

  if (pos != -1) {
    line.erase(0, pos + priorityStr.length() + 1);
    std::string data = line;
    boost::algorithm::trim_left(data);

    if ( !data.empty() ) {
      priority_t priority;
      bool flag = parsePriority(priorityStr, priority);
      if (flag) {
        queue.putElement(data, priority);
        return;
      }
    }
  }

  std::cout << "<INVALID COMMAND>\n";
}
