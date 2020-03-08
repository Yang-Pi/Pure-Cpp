#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <iostream>

enum class priority_t {
  HIGH,
  NORMAL,
  LOW
};
bool parsePriority(std::string, priority_t&);

template <typename T>
class QueueWithPriority
{
public:
  void putElement(const T&, priority_t);
  bool getElement(T&);

  void accelerate();
  bool empty() const;
  void clear();

private:
  std::list< T > highPriority_;
  std::list < T > normalPriority_;
  std::list < T > lowPriority_;
};

template < typename T >
void QueueWithPriority< T >::putElement(const T & elem, priority_t priority)
{
  switch (priority) {
    case priority_t::HIGH :
      highPriority_.push_back(elem);
      break;

    case priority_t::NORMAL :
      normalPriority_.push_back(elem);
      break;

    case priority_t::LOW :
      lowPriority_.push_back(elem);
      break;
  }
}

template < typename T >
bool QueueWithPriority< T >::getElement(T& elem)
{
  if ( !highPriority_.empty() ) {
    elem = highPriority_.front();
    highPriority_.pop_front();
    return true;
  }

  if ( !normalPriority_.empty() ) {
    elem = normalPriority_.front();
    normalPriority_.pop_front();
    return true;
  }

  if ( !lowPriority_.empty() ) {
    elem = lowPriority_.front();
    lowPriority_.pop_front();
    return true;
  }
  else {
    return false;
  }
}

template < typename T >
void QueueWithPriority< T >::accelerate()
{
  if (!( this->empty() )) {
    auto iter = highPriority_.end();
    highPriority_.splice(iter, lowPriority_);
  }
};

template < typename T >
bool QueueWithPriority< T >::empty() const
{
  if ( highPriority_.empty() && normalPriority_.empty() && lowPriority_.empty() ) {
    return true;
  }
  else {
    return false;
  }
};

template < typename T >
void QueueWithPriority< T >::clear()
{
  highPriority_.clear();
  normalPriority_.clear();
  lowPriority_.clear();
}

#endif //QUEUE_WITH_PRIORITY_HPP
