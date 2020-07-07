#include <cstring>

#include "queue-with-priority.hpp"

bool parsePriority(std::string line, priority_t& priority)
{
  if (strcmp(line.data(), "high") == 0) {
    priority = priority_t::HIGH;
    return true;
  }

  if (strcmp(line.data(), "normal") == 0) {
    priority = priority_t::NORMAL;
    return true;
  }

  if (strcmp(line.data(), "low") == 0) {
    priority = priority_t::LOW;
    return true;
  }

  return false;
}
