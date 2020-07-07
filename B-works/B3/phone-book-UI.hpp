#ifndef PHONE_BOOK_UI_HPP
#define PHONE_BOOK_UI_HPP

#include <map>

#include "phone-book.hpp"

class PhoneBookUI
{
public:
  enum class moveWhere_t {
    FIRST,
    LAST
  };

  PhoneBookUI();

  void add(const PhoneBook::note_t& note);
  void store(const std::string& mark, const std::string& newMark);
  void insert(const bool after, const std::string& mark, const PhoneBook::note_t& note);
  void remove(const std::string& mark);
  std::string show(const std::string& mark);
  void move(const std::string& mark, int steps);
  void move(const std::string& mark, const std::string& keyWord);

  /*void next(const std::string& mark);
  void prev(const std::string& mark);*/

private:
  using typeMap = std::map< std::string, PhoneBook::iterator >;
  typeMap::iterator getIter(const std::string& mark, bool& flag);

  typeMap mapBookmarks_;
  PhoneBook phoneBook_;
};

#endif //PHONE_BOOK_UI_HPP
