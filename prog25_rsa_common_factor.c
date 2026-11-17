/* 25. RSA: if a plaintext block M has a common factor with n, then gcd(C, n) reveals p or q,
   so n can be factored and the private key found. YES, it helps the attacker. */
#include <stdio.h>

long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); }
long power(long b, long e, long m) { long r = 1; b %= m; while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; } return r; }
long inverse(long a, long m) { for (long i = 1; i < m; i++) if (a * i % m == 1) return i; return 0; }

int main() {
    long n = 3599, e = 31;          /* n = 59 * 61 */
    long M = 177;                   /* 177 = 3 * 59 shares the factor 59 with n */
    long C = power(M, e, n);
    printf("Plaintext block M = %ld, ciphertext C = M^e mod n = %ld\n", M, C);

    long p = gcd(C, n);             /* C also shares the factor with n */
    printf("gcd(C, n) = %ld  -> a factor of n found!\n", p);
    long q = n / p, phi = (p - 1) * (q - 1), d = inverse(e, phi);
    printf("p = %ld, q = %ld, phi = %ld, private key d = %ld\n", p, q, phi, d);
    printf("Decrypting C with d gives %ld\n", power(C, d, n));
    return 0;
}
