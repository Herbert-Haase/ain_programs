#include <stdio.h>

int _sum(int num, int sum) {
  if (num == 0)
    return sum;
  return _sum(num - 1, sum + num);
}

int __sum(int num, int sum) {
  while (1) {
    if (num == 0)
      return sum;
    sum = num + sum;
    num = num - 1;
    continue;
  }
}

int sum(int num) { return __sum(num, 0); }

int main(void) { printf("result is %d\n", sum(10)); }
