# Checkoff-03

## XOR Encryption
**Slideshow:** https://docs.google.com/presentation/d/18QNCISoQkpUqQKbBHpVjPsYPR60uskrvX3VPsbHW8vE/edit?slide=id.h2689d85d28728e51_4_392#slide=id.h2689d85d28728e51_4_392

### Topic Introduction
Bitwise **XOR ($\oplus$)** performs binary addition modulo 2. Because it acts as its own inverse (applying the exact same key twice restores the original bits) it serves as a core basic technique in systems programming and cryptography.

* **Symmetry & Ciphers:** Compared single-byte XOR, repeating-key XOR (`key[i % key_len]`), and the mathematically unbreakable One-Time Pad (OTP).
* **Cryptanalysis:** Analyzed how key reuse cancels out the key ($C_1 \oplus C_2 = P_1 \oplus P_2$), enabling crib dragging, frequency analysis, and bit-flipping attacks.
* **C Implementation:** Built a cipher and a 256-key brute-force cracker, exploring explicit `size_t` length tracking, CPU register widths, and the in-place XOR swap.
* **Real-World History:** Investigated XOR's role in RAID 5 parity, early GUI mouse cursors, and the 1963 Moscow–Washington hotline.
* **Key Reuse Erases Security:** XORing two ciphertexts encrypted with the same key strips the key away completely, exposing the raw XOR of both plaintexts.
* **XOR Can Break C Strings:** Any byte XORed with itself produces `0x00`, prematurely terminating strings if you rely on `strlen()` instead of explicit buffer lengths.
* **Compilers Avoid the XOR Swap:** Despite using zero extra memory, `a ^= b; b ^= a; a ^= b;` creates sequential data dependencies that prevent CPU parallelism—and zeroes out data if pointers alias.
