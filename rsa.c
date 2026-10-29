#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Recursive Euclidean algorithm
unsigned long gcd(unsigned long a, unsigned long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Extended Euclidean algorithm: find d where (a * d) % m == 1
unsigned long modInverse(unsigned long a, unsigned long m) {
    long long t = 0, newT = 1;
    long long r = (long long)m, newR = (long long)(a % m);
    while (newR != 0) {
        long long quotient = r / newR;
        long long nextT = t - quotient * newT;
        t = newT;
        newT = nextT;
        long long nextR = r - quotient * newR;
        r = newR;
        newR = nextR;
    }
    if (r != 1) return 0;
    if (t < 0) t += (long long)m;
    return (unsigned long)t;
}

// Multiply modulo n without overflowing unsigned long
static unsigned long addMod(unsigned long a, unsigned long b, unsigned long n) {
    return a >= n - b ? a - (n - b) : a + b;
}
static unsigned long mulMod(unsigned long a, unsigned long b, unsigned long n) {
    unsigned long result = 0;
    a %= n;
    while (b > 0) {
        if (b & 1UL) result = addMod(result, a, n);
        b >>= 1;
        if (b) a = addMod(a, a, n);
    }
    return result;
}
static unsigned long powerMod(unsigned long base, unsigned long exponent, unsigned long n) {
    unsigned long result = 1 % n;
    base %= n;
    while (exponent > 0) {
        if (exponent & 1UL) result = mulMod(result, base, n);
        exponent >>= 1;
        if (exponent) base = mulMod(base, base, n);
    }
    return result;
}

// Trial-division primality check for small educational examples.
static int isPrime(unsigned long value) {
    if (value < 2) return 0;
    for (unsigned long divisor = 2; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) return 0;
    }
    return 1;
}

void generateKeys(unsigned long p, unsigned long q, unsigned long *n, unsigned long *e, unsigned long *d) {
    if (!isPrime(p) || !isPrime(q) || p == q || p > 1000 || q > 1000) {
        fprintf(stderr, "Enter two different prime numbers between 2 and 1000.\n");
        exit(EXIT_FAILURE);
    }
    *n = p * q;
    unsigned long phi = (p - 1) * (q - 1);
    if (phi > LLONG_MAX) {
        fprintf(stderr, "Numbers too large for modular inverse.\n");
        exit(EXIT_FAILURE);
    }
    printf("For p = %lu and q = %lu --> phi = %lu\n", p, q, phi);
    for (unsigned long candidate = 2; candidate < phi; ++candidate) {
        if (gcd(candidate, phi) == 1)
            printf("  Here is e=%lu such that 1 < e < phi and gcd(e, phi) = 1\n", candidate);
    }
    printf("Select one of the above as e: ");
    if (scanf("%lu", e) != 1 || *e <= 1 || *e >= phi || gcd(*e, phi) != 1) {
        fprintf(stderr, "Invalid e value.\n");
        exit(EXIT_FAILURE);
    }
    *d = modInverse(*e, phi);
    if (*d == 0) {
        fprintf(stderr, "Modular inverse not found.\n");
        exit(EXIT_FAILURE);
    }
}

unsigned long encrypt(unsigned long plaintext, unsigned long e, unsigned long n) {
    return powerMod(plaintext, e, n);
}

unsigned long decrypt(unsigned long ciphertext, unsigned long d, unsigned long n) {
    return powerMod(ciphertext, d, n);
}

int main(void) {
    unsigned long p, q, n, e, d;
    printf("Enter p and q: ");
    if (scanf("%lu %lu", &p, &q) != 2) return 1;
    generateKeys(p, q, &n, &e, &d);
    printf("Public key (e, n): (%lu, %lu)\n", e, n);
    printf("Private key (d, n): (%lu, %lu)\n\n", d, n);

    unsigned long plaintext;
    printf("Enter an integer between 0 and n-1 as plain text to be encrypted: ");
    if (scanf("%lu", &plaintext) != 1 || plaintext >= n) {
        fprintf(stderr, "Plaintext must be between 0 and %lu.\n", n - 1);
        return 1;
    }
    printf("Original plaintext: %lu\n", plaintext);
    unsigned long ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lu\n", ciphertext);
    unsigned long decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lu\n\n", decrypted);
    return 0;
}
