# RSA Encryption in C

An interactive, educational implementation of RSA public-key encryption in C.

## Features
- Recursive Euclidean algorithm for GCD
- Modular inverse using the extended Euclidean algorithm
- Public and private RSA key generation
- Modular exponentiation for encryption and decryption
- Input validation for distinct small prime numbers and plaintext range

## Build and run

```bash
gcc -std=c11 -Wall -Wextra -pedantic rsa.c -o rsa
./rsa
```

On Windows with GCC, run `rsa.exe` instead of `./rsa`.

## Example
Enter `3 11` for the prime numbers, `7` for the public exponent, and `30` for the plaintext.

Expected results:

```text
Public key (e, n): (7, 33)
Private key (d, n): (3, 33)
Original plaintext: 30
Encrypted ciphertext: 24
Decrypted plaintext: 30
```

## How it works
1. Calculate `n = p * q` and `phi = (p - 1) * (q - 1)`.
2. Choose a public exponent `e` relatively prime to `phi`.
3. Calculate the modular inverse `d` of `e` modulo `phi`.
4. Encrypt a plaintext integer using `ciphertext = plaintext^e mod n`.
5. Decrypt using `plaintext = ciphertext^d mod n`.

## Limitations
This is a **toy implementation for learning**, not secure production cryptography. It uses small primes, does not use cryptographic padding or secure random key generation, and prints the private key. The input prime numbers are intentionally limited to 1000 for manageable console output.

## Attribution
Adapted from a university programming assignment. Instructor-provided starter materials are not included. Keep this repository private until the course sharing policy is confirmed.
