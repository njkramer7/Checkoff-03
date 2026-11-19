#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Same function works for both encrypting and decrypting
void xor_cipher(uint8_t *data, size_t data_len, const uint8_t *key, size_t key_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

void print_hex(const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main(void) {
    char message[] = "Systems Programming!";
    const char key[] = "KEY";

    size_t msg_len = strlen(message);
    size_t key_len = strlen(key);

    printf("Original:  %s\n", message);

    // 1. Encrypt in place
    xor_cipher((uint8_t *)message, msg_len, (const uint8_t *)key, key_len);
    printf("Encrypted: ");
    print_hex((uint8_t *)message, msg_len);

    // 2. Decrypt in place (exact same call)
    xor_cipher((uint8_t *)message, msg_len, (const uint8_t *)key, key_len);
    printf("Decrypted: %s\n", message);

    return 0;
}