#ifndef ISEQUAL_ISEQUAL_HPP
#define ISEQUAL_ISEQUAL_HPP

#include <cstdint>

#include <string>

#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#define CHECKSIZE(op1, op2) \
if (op1.size() != op2.size()) \
{ \
  return false; \
} \

template <class T>
bool isEqual(const T& op1, const T& op2);

template <class T, template<class> class LIST>
bool isEqualList(const LIST<T>& op1, const LIST<T>& op2)
{
  CHECKSIZE(op1, op2)
  auto first = std::mismatch(op1.begin(), op1.end(), op2.begin(), isEqual<T>);
  return (first == std::make_pair(op1.end(), op2.end()));
}

#define LISTEQUAL(LIST) \
template <class T> \
bool isEqual(const LIST<T>& op1, const LIST<T>& op2) \
{ \
  return isEqualList(op1, op2); \
} \

LISTEQUAL(std::vector)
LISTEQUAL(std::deque)
LISTEQUAL(std::forward_list)
LISTEQUAL(std::list)
LISTEQUAL(std::set)
LISTEQUAL(std::multiset)

template <class T>
bool isEqual(const std::unordered_set<T>& op1, const std::unordered_set<T>& op2)
{
  std::set<T> op1_temp;
  std::set<T> op2_temp;
  op1_temp.insert(op1.begin(), op1.end());
  op2_temp.insert(op2.begin(), op2.end());
  return isEqual(op1_temp, op2_temp);
}

template <class T>
bool isEqual(
  const std::unordered_multiset<T>& op1,
  const std::unordered_multiset<T>& op2)
{
  std::multiset<T> op1_temp;
  std::multiset<T> op2_temp;
  op1_temp.insert(op1.begin(), op1.end());
  op2_temp.insert(op2.begin(), op2.end());
  return isEqual(op1_temp, op2_temp);
}

template <class T1, class T2>
bool isEqualPair(const std::pair<T1, T2>& op1, const std::pair<T1, T2>& op2)
{
  return (isEqual(op1.first, op2.first) && isEqual(op1.second, op2.second));
}

template <class T1, class T2>
bool isEqual(const std::pair<T1, T2>& op1, const std::pair<T1, T2>& op2)
{
  return isEqualPair<T1, T2>(op1, op2);
}

template <class K, class V>
bool isEqual(const std::map<K, V>& op1, const std::map<K, V>& op2)
{
  CHECKSIZE(op1, op2)
  auto first = std::mismatch(op1.begin(), op1.end(), op2.begin(), isEqualPair<K, V>);
  return (first == make_pair(op1.end(), op2.end()));
}

template <class K, class V>
bool isEqual(const std::multimap<K, V>& op1, const std::multimap<K, V>& op2)
{
  CHECKSIZE(op1, op2)
  bool is_first = true;
  for(auto x1 = op1.first, x2 = op2.first; x1 != op1.end(); ++x1, ++x2)
  {
    K key1, key2;
    std::multiset<V> value1, value2;
    if (!isEqual(x1->key, x2->key))
    {
      return false;
    }
    if (is_first)
    {
      key1 = x1->key;
      key2 = x2->key;
      value1.clear();
      value2.clear();
      value1.insert(x1->value);
      value2,insert(x2->value);
    }
    else
    {
      if !(isEqual(key1, x1->key)&&(isEqual(key2, x2->key)))
      {
        if !isEqual(value1, value2)
        {
          return false;
        }
        key1 = x1->key;
        key2 = x2->key;
        value1.clear();
        value2.clear();
      }
      value1.insert(x1->value);
      value2.insert(x2->value);
    }
  }
  return isEqual(value1, value2);
}

template <class K, class V>
bool isEqual(const std::unordered_map<K, V>& op1, const std::unordered_map<K, V>& op2)
{
  CHECKSIZE(op1, op2)
  std::map<K, V> op1_temp;
  op1_temp.insert(op1.begin(), op1.end());
  std::map<K, V> op2_temp;
  op2_temp.insert(op2.begin(), op2.end());
  return isEqual(op1_temp, op2_temp);
}

template <class K, class V>
bool isEqual(const std::unordered_multimap<K, V>& op1, const std::unordered_multimap<K, V>& op2)
{
  CHECKSIZE(op1, op2)
  std::multimap<K, V> op1_temp;
  op1_temp.insert(op1.begin(), op1.end());
  std::multimap<K, V> op2_temp;
  op2_temp.insert(op2.begin(), op2.end());
  return isEqual(op1_temp, op2_temp);
}


#endif
