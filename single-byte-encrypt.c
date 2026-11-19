#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    const char *plaintext = "Systems programming makes bitwise ops fun!";
    uint8_t key = 0x5A; // Secret 1-byte key (90 in decimal)
    size_t len = strlen(plaintext);

    for (size_t i = 0; i < len; i++) {
        uint8_t cipher_byte = (uint8_t)plaintext[i] ^ key;
        printf("%02x", cipher_byte);
    }
    printf("\n");

    return 0;
}