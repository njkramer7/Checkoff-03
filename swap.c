#include <stdio.h>

void xor_swap(int *a, int *b) {
    // Crucial guard: if both pointers point to the exact same memory address,
    // *a ^= *b will immediately zero out the value!
    if (a == b) {
        return;
    }

    *a ^= *b; // Step 1: *a holds (a_orig ^ b_orig)
    *b ^= *a; // Step 2: *b becomes b_orig ^ (a_orig ^ b_orig) = a_orig
    *a ^= *b; // Step 3: *a becomes (a_orig ^ b_orig) ^ a_orig = b_orig
}

int main(void) {
    int x = 42; // 00101010 in binary
    int y = 99; // 01100011 in binary

    printf("Before swap: x = %d, y = %d\n", x, y);

    xor_swap(&x, &y);

    printf("After swap:  x = %d, y = %d\n", x, y);

    return 0;
}