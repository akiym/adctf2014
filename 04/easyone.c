#include <stdio.h>

// ADCTF_7H15_15_7oO_345y_FOR_M3

int main (void) {
    char password[30], input[30];
    char *p1, *p2;
    p1 = password;
    p2 = input;

    printf("password: ");
    scanf("%29s", input);

    password[6] = '7';
    password[18] = '3';
    password[11] = '1';
    password[7] = 'H';
    password[14] = '7';
    password[24] = 'O';
    password[20] = '5';
    password[9] = '5';
    password[16] = 'O';
    password[22] = '_';
    password[21] = 'y';
    password[28] = '3';
    password[2] = 'C';
    password[25] = 'R';
    password[8] = '1';
    password[3] = 'T';
    password[12] = '5';
    password[23] = 'F';
    password[0] = 'A';
    password[26] = '_';
    password[27] = 'M';
    password[13] = '_';
    password[10] = '_';
    password[15] = 'o';
    password[5] = '_';
    password[19] = '4';
    password[4] = 'F';
    password[17] = '_';
    password[1] = 'D';
    password[29] = '\0';

    while (1) {
        if (*p1 != *p2) {
            printf("wrong\n");
            return 1;
        }
        if (*p1 == '\0' && *p2 == '\0') {
            break;
        }
        p1++;
        p2++;
    }

    printf("correct. the flag is: %s\n", input);

    return 0;
}
