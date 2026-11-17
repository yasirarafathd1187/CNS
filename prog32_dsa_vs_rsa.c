/* 32. DSA uses a fresh random k for every signature, so signing the same message twice gives
   different signatures (probabilistic). RSA signatures are deterministic: same message -> same signature.
   Implication: DSA signatures cannot be compared/linked by value, and k must never be reused or
   leaked (otherwise the private key can be computed). Toy numbers are used here. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long power(long b, long e, long m) { long r = 1; b %= m; while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; } return r; }
long inverse(long a, long m) { for (long i = 1; i < m; i++) if (a * i % m == 1) return i; return 0; }

void dsa_sign(long H, long x, long k, long p, long q, long g, long *r, long *s) {
    *r = power(g, k, p) % q;
    *s = inverse(k, q) * (H + x * *r) % q;
}

int main() {
    long p = 23, q = 11, g = 4, x = 3;      /* DSA: q divides p-1, g has order q, x = private key */
    long H = 5;                             /* hash of the message */
    long r, s;
    srand(time(0));

    printf("DSA - same message signed 3 times:\n");
    for (int i = 0; i < 3; i++) {
        long k;
        do { k = 1 + rand() % (q - 1); dsa_sign(H, x, k, p, q, g, &r, &s); } while (r == 0 || s == 0);
        printf("  k = %2ld -> signature (r, s) = (%ld, %ld)\n", k, r, s);
    }

    long n = 3599, d = 3031;                /* toy RSA signature s = H^d mod n */
    printf("\nRSA - same message signed 3 times:\n");
    for (int i = 0; i < 3; i++) printf("  signature = %ld\n", power(H, d, n));
    return 0;
}
