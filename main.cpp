#include "operations.h"

int main() {
  Number x = (Number)123456789012345678LL;
  Number y = (Number)987654321012345678LL;
  Number r = multiply(x, y);
  std::cout << to_string128(r) << "\n";
  return 0;
}