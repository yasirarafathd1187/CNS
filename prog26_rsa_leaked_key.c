/* 26. RSA: Bob leaks his private key d and picks a new (e, d) with the SAME modulus n. NOT safe:
   e*d - 1 is a multiple of phi(n), which lets anyone factor n. */
#include <stdio.h>

long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); }
long power(long b, long e, long m) { long r = 1; b %= m; while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; } return r; }

int main() {
    long n = 3599, e = 31, d = 3031;       /* leaked key pair */
    long k = e * d - 1, r = k, t = 0;
    while (r % 2 == 0) { r /= 2; t++; }    /* k = 2^t * r */

    for (long g = 2; g < 50; g++) {
        long x = power(g, r, n);
        if (x == 1 || x == n - 1) continue;
        for (long i = 0; i < t; i++) {
            long y = x * x % n;
            if (y == 1) {                   /* x is a non-trivial square root of 1 */
                long p = gcd(x - 1, n);
                printf("Using g = %ld: factors found  p = %ld, q = %ld\n", g, p, n / p);
                printf("phi(n) = %ld -> attacker can compute any new private key of Bob.\n", (p - 1) * (n / p - 1));
                return 0;
            }
            x = y;
        }
    }
    printf("Try more values of g\n");
    return 0;
}
