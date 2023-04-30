#include <stdint.h>

#define CONSTANT 42

int f(int x) {
  int result = (x / CONSTANT);
  return result;
}