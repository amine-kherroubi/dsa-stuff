#include <climits>
#include <cstdlib>
#include <stdexcept>

int integerDivide(int dividend, int divisor) {
  if (divisor == 0) {
    throw std::runtime_error("Can't divide by zero");
  }

  if (dividend == INT_MIN && divisor == -1)
    return INT_MAX;

  bool negative = (dividend < 0) ^ (divisor < 0);

  long long a = std::llabs((long long)dividend);
  long long b = std::llabs((long long)divisor);

  long long quotient = 0;

  while (a >= b) {
    long long temp = b, multiple = 1;
    while ((temp << 1) <= a) {
      temp <<= 1;
      multiple <<= 1;
    }
    a -= temp;
    quotient += multiple;
  }

  if (negative)
    quotient = -quotient;

  if (quotient > INT_MAX)
    quotient = INT_MAX;
  if (quotient < INT_MIN)
    quotient = INT_MIN;

  return static_cast<int>(quotient);
}
