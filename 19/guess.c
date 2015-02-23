#include <stdio.h>

/*
   x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9 + x10 + x11 + x12 = 0x0421bed3
*/

#define KEY_SIZE 256

int results[12] = {
    0x8711597e, 0xf82e6b11, 0xfb84adf9, 0x4b1fbd36, 0x3883b5e6, 0xda3cb6d8, 0xacaf25bd, 0x7e88fa4a, 0xcd7069e4, 0x9751e9ff, 0x7de09e8b, 0x7e63456f
};

int init_key = 0xdeadbeef;
int key_table[KEY_SIZE] = {0};
int ki;

// G00dGu3SS1ng
void init_key_table(void) {
    for (; ki < KEY_SIZE-1; ki++) {
        if (key_table[ki] == 0) {
            key_table[ki] = init_key;
        } else {
            if (((ki + 1) & 2) != 0) {
                key_table[ki] += key_table[ki-2];
            }
        }
        key_table[ki+1] = (key_table[ki] * (ki << 1)) + (key_table[ki] / (ki + 1));
    }
}

int calc_key() {
    int n = key_table[ki];
    ki++;
    return n;
}

int check_length(double len) {
    int ok = 0;
    len /= (1 << 16);

    if (len == 0.00018310546875) {
        return ok;
    }
    goto WRONG;

  WRONG:
    return !ok;
}

int main(int argc, char const* argv[])
{
    if (argc != 2) {
        goto WRONG;
    }

    int d0;
    size_t len;
    asm volatile("repne\n\t"
        "scasb"
        : "=c" (len), "=&D" (d0)
        : "1" (argv[1]), "a" (0), "0" (0xffffffffu)
        : "memory");
    len = ~len - 1;

    if (check_length(len) == 1) {
        goto WRONG;
    }

    init_key_table();

    int i, j, result;
    for (i = 0; i < len; i++) {
        char c = argv[1][i];
        ki = c + i;
        if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
        } else {
            goto WRONG;
        }
        result = 0;
        for (j = 0; j < len; j++) {
            result += calc_key();
        }
        if (result != results[i]) {
            goto WRONG;
        }
    }

    printf("you got flag: ADCTF_%s\n", argv[1]);
    return 0;

  WRONG:
    return 1;
}
