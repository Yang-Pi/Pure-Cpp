#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>
#include <list>

class PhoneBook
{
public:
  struct note_t {
    std::string number;
    std::string name;
  };

  using iterator = std::list< note_t >::iterator;

  iterator insertNote(const iterator pos, const note_t& newNote);
  iterator deleteNote(const iterator pos);
  iterator moveNote(iterator pos, int steps);
  std::string getNote(const iterator pos) const;

  iterator begin();
  iterator end();
  iterator next(iterator pos, bool& flag);
  iterator prev(iterator pos, bool& flag);

  size_t getSize() const;
  bool isEmpty() const;

private:
  std::list< note_t > listNotes_;
};

#endif //PHONE_BOOK_HPP
