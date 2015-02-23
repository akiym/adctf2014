/* gcc -O2 -m32 -masm=intel -fno-stack-protector -o easypwn.o -c easypwn.c
 * ld -m elf_i386 -o easypwn easypwn.o
 */
void syscall(int b, int c, int d) {
    asm volatile(
        "int 0x80\n\t"
        :
        : "b" (b), "c" (c), "d" (d)
        :);
}

void pwn_me(void) {
    char name[16];

    char volatile *message = "pwn me: ";
    asm volatile(
        "mov eax, 0x04\n\t"
        "push 8\n\t"
        "push %0\n\t"
        "push 1\n\t"
        "call esi\n\t"
        "add esp, 12\n\t"
        :
        : "c" (message)
        :);

    asm volatile(
        "mov eax, 0x03\n\t"
        "push 128\n\t"
        "push %0\n\t"
        "push 0\n\t"
        "call esi\n\t"
        "add esp, 12\n\t"
        :
        : "c" (name)
        :);
}

void _start(void) {
    asm volatile(
        "call pwn_me\n\t"
        :
        : "S" (syscall)
        :);

    char volatile *message = "☆（ゝω・）v\n";
    asm volatile(
        "mov eax, 0x04\n\t"
        "push 19\n\t"
        "push %0\n\t"
        "push 1\n\t"
        "call esi\n\t"
        "add esp, 12\n\t"
        :
        : "c" (message)
        :);
    asm volatile(
        "mov eax, 0x01\n\t"
        "push 0\n\t"
        "call esi\n\t"
        "add esp, 4\n\t"
        :
        :
        :);
}
