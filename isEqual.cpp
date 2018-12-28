#include "isEqual.hpp"

using namespace std;

template <class T>
bool isEqual(const T& op1, const T& op2)
{
  return (op1 == op2);
}

template <class T>
bool isEqualReal(const T& op1, const T& op2)
{
  constexpr T err = 1e-6;
  T diff = abs(op1 - op2);
  return (diff < err);
}

#define SIMPLEEQUAL(T) \
template \
bool isEqual<T>(const T& op1, const T& op2);

SIMPLEEQUAL(string)
SIMPLEEQUAL(bool)

SIMPLEEQUAL(int8_t)
SIMPLEEQUAL(int16_t)
SIMPLEEQUAL(int32_t)
SIMPLEEQUAL(int64_t)

SIMPLEEQUAL(uint8_t)
SIMPLEEQUAL(uint16_t)
SIMPLEEQUAL(utin32_t)
SIMPLEEQUAL(uint64_t)

#define REALEQUAL(T)
template \
bool isEqual<T>(const T& op1, const T& op2) \
{ \
  return isEqualReal<T>(op1, op2); \
} \
template \
bool isEqual<T>(const T& op1, const T& op2); \

REALEQUAL(float)
REALEQUAL(double)
REALEQUAL(long double)

#endif
