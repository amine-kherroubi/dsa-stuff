#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using Number = __int128;
using String = std::string;
using Error = std::runtime_error;

static String to_string128(Number x) {
  if (x == 0)
    return "0";
  bool neg = x < 0;
  if (neg)
    x = -x;
  String s;
  while (x > 0) {
    s.push_back(char('0' + (x % 10)));
    x /= 10;
  }
  if (neg)
    s.push_back('-');
  std::reverse(s.begin(), s.end());
  return s;
}

inline Number power(Number a, Number b) {
  if (b < 0)
    throw Error("Negative exponent");
  if (a == 0 && b == 0)
    throw Error("0^0 undefined");
  if (b == 0)
    return 1;
  Number res = 1, base = a;
  while (b > 0) {
    if (b & 1)
      res *= base;
    base *= base;
    b >>= 1;
  }
  return res;
}

inline Number divide_positive(Number dividend, Number divisor) {
  if (divisor == 0)
    throw Error("Divide by zero");
  if (dividend < 0 || divisor < 0)
    throw Error("divide_positive expects non-negative inputs");

  Number a = dividend;
  Number b = divisor;
  Number q = 0;

  while (a >= b) {
    Number temp = b;
    Number multiple = 1;
    while (temp <= (a >> 1)) {
      temp <<= 1;
      multiple <<= 1;
    }
    a -= temp;
    q += multiple;
  }
  return q;
}

inline Number divide(Number dividend, Number divisor) {
  if (divisor == 0)
    throw Error("Divide by zero");
  bool neg = (dividend < 0) ^ (divisor < 0);
  Number a = dividend < 0 ? -dividend : dividend;
  Number b = divisor < 0 ? -divisor : divisor;
  Number q = divide_positive(a, b);
  return neg ? -q : q;
}

inline Number multiply_positive(Number a, Number b) {
  if (a < 10 && b < 10)
    return a * b;

  Number tmp = a;
  Number digits = 0;
  while (tmp > 0) {
    digits++;
    tmp /= 10;
  }
  if (digits == 0)
    digits = 1;

  Number m = digits / 2;
  Number tens = power((Number)10, m);

  Number a0 = a % tens;
  Number a1 = divide_positive(a, tens);
  Number b0 = b % tens;
  Number b1 = divide_positive(b, tens);

  Number z0 = multiply_positive(a0, b0);
  Number z2 = multiply_positive(a1, b1);
  Number z1 = multiply_positive(a0 + a1, b0 + b1) - z0 - z2;

  return z2 * power((Number)10, 2 * m) + z1 * power((Number)10, m) + z0;
}

inline Number multiply(Number a, Number b) {
  if (a == 0 || b == 0)
    return 0;
  bool neg = (a < 0) ^ (b < 0);
  Number aa = a < 0 ? -a : a;
  Number bb = b < 0 ? -b : b;
  Number r = multiply_positive(aa, bb);
  return neg ? -r : r;
}