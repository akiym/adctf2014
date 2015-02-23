#include <stdio.h>
#include <string.h>

int main() {
  char flag[] = "ADCTF_51mpl3_X0R_R3v3r51n6";
  int len = strlen(flag);
  for (int i = 0; i < len; i++) {
    if (i > 0) flag[i] ^= flag[i-1];
    flag[i] ^= flag[i] >> 4;
    flag[i] ^= flag[i] >> 3;
    flag[i] ^= flag[i] >> 2;
    flag[i] ^= flag[i] >> 1;
    printf("%02x", (unsigned char)flag[i]);
  }
  return 0;
}
