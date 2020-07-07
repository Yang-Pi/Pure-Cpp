#include <iterator>

#include "phone-book.hpp"

PhoneBook::iterator PhoneBook::insertNote(const iterator pos, const note_t& newNote)
{
  return listNotes_.insert(pos, newNote);
}

PhoneBook::iterator PhoneBook::deleteNote(const iterator pos)
{
  if (pos != listNotes_.end()){
    return listNotes_.erase(pos);
  }
  else {
    return pos;
  }
  /*else {
    throw std::invalid_argument("Try to delete element which is out of list!\n");
  }*/
}

PhoneBook::iterator PhoneBook::moveNote(iterator pos, int steps)
{
  int distance = 0;
  if (steps > 0) {
    distance = std::distance(pos, listNotes_.end()) - 1;
  }
  else {
    distance = std::distance(pos, listNotes_.begin());
  }

  if (steps > distance) {
    steps = distance;
  }
  std::advance(pos, steps);

  return pos;
}

std::string PhoneBook::getNote(const iterator pos) const
{
  if (pos != listNotes_.end()) {
    return pos->number + " " + pos->name;
  }
  else {
    return "";
  }
}

PhoneBook::iterator PhoneBook::begin()
{
  return listNotes_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return listNotes_.end();
}

PhoneBook::iterator PhoneBook::next(iterator pos, bool& flag)
{
  if (std::next(pos) != listNotes_.end()) {
    ++pos;
    flag = 0;
  }
  else {
    flag = 1;
  }

  return pos;
}

PhoneBook::iterator PhoneBook::prev(iterator pos, bool& flag)
{
  if (pos != listNotes_.begin()) {
    --pos;
    flag = 0;
  }
  else {
    flag = 1;
  }

  return pos;
}

size_t PhoneBook::getSize() const
{
  return listNotes_.size();
}

bool PhoneBook::isEmpty() const
{
  return listNotes_.empty();
}
