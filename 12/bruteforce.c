/* gcc -O2 -masm=intel bruteforce.c -o bruteforce */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h>

int NOT_PRIME = 0;

struct timespec tim1 = {0,10000000}, tim2;

jmp_buf env;

static inline void mysleep() {
    asm volatile(
        "mov r14, rcx\n\t"
        "mov rdx, rdi\n\t"
        "mov rdi, %0\n\t"
        "mov rsi, %1\n\t"
        "xor rax, rax\n\t"
        "mov al, 0x23\n\t"
        "syscall\n\t"
        "mov rdi, rdx\n\t"
        "mov rcx, r14\n\t"
        "xor esi, esi\n\t"
        :
        : "r" (&tim1), "r" (&tim2)
        :);
}

void signal_handler (int signo, siginfo_t *si, void *data) {
    switch (signo) {
    case SIGFPE:
        NOT_PRIME = 1;
        siglongjmp(env, signo);
        break;
    }
}

int is_prime(int n) {
    int i;
    for (i = 2; i < n; i++) {
        mysleep();
        volatile int x = 1 / (n % i);
    }
}

int main(void) {
    int n = 0;
    int i = 2;

    struct sigaction sa, osa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigaction(SIGFPE, &sa, &osa);

    setbuf(stdout, NULL);
    while (1) {
        mysleep();
        NOT_PRIME = 0;
        if (sigsetjmp(env, 1) == 0) {
            is_prime(i);
        }
        if (!NOT_PRIME) {
            mysleep();
            if (n % 10 == 0) {
                printf("\rcalculating");
            } else if (n % 1 == 0) {
                printf(".");
            }
            n++;
            if (n == tim1.tv_nsec) { // 179424673
                printf("the flag is: ADCTF_%d\n", i);
                break;
            }
        }
        i++;
    }
    return 0;
}
