#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

#include "phone-book-UI.hpp"

const std::string CURRENT_MARK = "current";

PhoneBookUI::PhoneBookUI()
{
  mapBookmarks_[CURRENT_MARK] = phoneBook_.end();
}

void PhoneBookUI::add(const PhoneBook::note_t& note)
{
  phoneBook_.insertNote(phoneBook_.end(), note);

  if (phoneBook_.getSize() == 1) {
    mapBookmarks_[CURRENT_MARK] = phoneBook_.begin();
  }
}

void PhoneBookUI::store(const std::string& mark, const std::string& newMark)
{
  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    auto ret = mapBookmarks_.emplace(newMark, markIter->second);

    if (!ret.second) {
      std::cout << "Such bookmark is alredy exists!\n";
    }
  }
}

void PhoneBookUI::insert(const bool after, const std::string& mark, const PhoneBook::note_t& note)
{
  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    PhoneBook::iterator insertIter = markIter->second;

    if (insertIter != phoneBook_.end()) {
      if (after == true) {
        insertIter = std::next(insertIter);
      }
      phoneBook_.insertNote(insertIter, note);
    }
    else {
      add(note);
    }
  }
}

void PhoneBookUI::remove(const std::string& mark)
{
  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    if (!phoneBook_.isEmpty()) {
      PhoneBook::iterator deleteIter = markIter->second;

      size_t phoneBookSize = phoneBook_.getSize();
      bool flag = false;
      std::for_each(mapBookmarks_.begin(), mapBookmarks_.end(), [&](auto &mapIter) {
        if (mapIter.second == deleteIter) {
          mapIter.second = ((std::next(mapIter.second) == phoneBook_.end()) && (phoneBookSize > 1)) ?
              phoneBook_.prev(deleteIter, flag) : phoneBook_.next(deleteIter, flag);
        }
      });

      deleteIter = phoneBook_.deleteNote(deleteIter);
    }
    else {
      std::cout << "<EMPTY>\n";
    }
  }
}

std::string PhoneBookUI::show(const std::string& mark)
{
  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    if (!phoneBook_.isEmpty()) {
      PhoneBook::iterator showIter = markIter->second;
      return phoneBook_.getNote(showIter);
    }
    else {
      std::cout << "<EMPTY>";
      return "";
    }
  }
  else {
    return "";
  }
}

void PhoneBookUI::move(const std::string& mark, int steps)
{
  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    markIter->second = phoneBook_.moveNote(markIter->second, steps);
  }
}

void PhoneBookUI::move(const std::string& mark, const std::string& keyWord)
{
  moveWhere_t where;

  if (keyWord == "first") {
    where = moveWhere_t::FIRST;
  }
  else if (keyWord == "last") {
    where = moveWhere_t::LAST;
  }
  else {
    std::cout << "<INVALID STEP>\n";
    return;
  }

  bool flag = false;
  typeMap::iterator markIter = getIter(mark, flag);

  if (!flag) {
    markIter->second = (where == moveWhere_t::FIRST) ? phoneBook_.begin() : --phoneBook_.end();
  }
}

PhoneBookUI::typeMap::iterator PhoneBookUI::getIter(const std::string& mark, bool& flag)
{
  typeMap::iterator markIter = mapBookmarks_.find(mark);

  if (markIter != mapBookmarks_.end()) {
    flag = false;
  }
  else {
    std::cout << "<INVALID BOOKMARK>";
    flag = true;
  }

  return markIter;
}
