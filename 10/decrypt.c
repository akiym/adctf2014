#include <stdio.h>
#include <string.h>

// http://ichirin2501.hatenablog.com/entry/2012/06/10/195026
char unshiftL(char y, int t) {
  char x;
  char z = (y & (1U << t) - 1) << t;
  char mask = ((1U << t) - 1) << t;

  while (mask) {
    x = z ^ y;
    z = z | ((x & mask) << t);
    mask <<= t;
  }
  return x;
}

char unshiftR(char y, int t) {
  char x;
  char z = (y & (((1U << t) - 1) << (8 - t))) >> t;
  char mask = (((1U << t) - 1) << (8 - t)) >> t;

  while (mask) {
    x = z ^ y;
    z = z | ((x & mask) >> t);
    mask >>= t;
  }
  return x;
}

int main() {
  char flag[] = "ADCTF_51mpl3_X0R_R3v3r51n6";
  int len = strlen(flag);
  for (int i = 0; i < len; i++) {
    if (i > 0) flag[i] ^= flag[i-1];
    flag[i] ^= flag[i] >> 4;
    flag[i] ^= flag[i] >> 3;
    flag[i] ^= flag[i] >> 2;
    flag[i] ^= flag[i] >> 1;
  }

  char buf = 0;
  for (int i = 0; i < len; i++) {
    int f = flag[i];
    flag[i] = unshiftR(flag[i], 1);
    flag[i] = unshiftR(flag[i], 2);
    flag[i] = unshiftR(flag[i], 3);
    flag[i] = unshiftR(flag[i], 4);
    if (i > 0) flag[i] ^= buf;
    buf = f;
    printf("%c", flag[i]);
  }
  return 0;
}
