#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Simple heuristic: reward common English characters, heavily penalize non-printable bytes
int score_english(const uint8_t *buf, size_t len) {
    int score = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buf[i];
        if (c == ' ') {
            score += 10;
        } else if (isalpha(c)) {
            char lower = (char)tolower(c);
            if (strchr("etaoinshrdlu", lower)) {
                score += 6; // Most common English letters
            } else {
                score += 3;
            }
        } else if (isprint(c)) {
            score += 1; // Numbers and punctuation
        } else if (c != '\n' && c != '\r' && c != '\t') {
            score -= 20; // Non-printable garbage
        }
    }
    return score;
}

// Convert a hex string (e.g. "0923...") into raw bytes
size_t hex_to_bytes(const char *hex, uint8_t *out, size_t max_len) {
    size_t hex_len = strlen(hex);
    size_t byte_len = hex_len / 2;
    if (byte_len > max_len) byte_len = max_len;

    for (size_t i = 0; i < byte_len; i++) {
        unsigned int val;
        sscanf(hex + 2 * i, "%2x", &val);
        out[i] = (uint8_t)val;
    }
    return byte_len;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <hex_ciphertext>\n", argv[0]);
        return 1;
    }

    uint8_t cipher[1024];
    uint8_t candidate[1024];
    uint8_t best_plain[1025]; // +1 for null terminator

    size_t len = hex_to_bytes(argv[1], cipher, sizeof(cipher));

    int best_score = -1000000;
    uint8_t best_key = 0;

    // Try all 256 possible 1-byte keys
    for (int k = 0; k < 256; k++) {
        for (size_t i = 0; i < len; i++) {
            candidate[i] = cipher[i] ^ (uint8_t)k;
        }

        int score = score_english(candidate, len);
        if (score > best_score) {
            best_score = score;
            best_key = (uint8_t)k;
            memcpy(best_plain, candidate, len);
            best_plain[len] = '\0';
        }
    }

    printf("Cracked Key: 0x%02X ('%c')\n", best_key, isprint(best_key) ? best_key : '?');
    printf("Plaintext:   %s\n", best_plain);

    return 0;
}