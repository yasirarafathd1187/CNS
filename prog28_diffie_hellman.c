/* 28. Diffie-Hellman variant: send x^a mod q instead of a^x mod q.
   This is BROKEN: Eve computes b = a^-1 mod (q-1) and then x = (x^a)^b mod q (easy,
   no discrete logarithm needed). So Eve finds the secret numbers directly. */
#include <stdio.h>

long power(long b, long e, long m) { long r = 1; b %= m; while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; } return r; }
long inverse(long a, long m) { for (long i = 1; i < m; i++) if (a * i % m == 1) return i; return 0; }

int main() {
    long q = 23, a = 5;                 /* public: prime q and exponent a, gcd(a, q-1) = 1 */
    long xA = 6, xB = 15;               /* secret numbers */
    long A = power(xA, a, q), B = power(xB, a, q);
    printf("Alice sends xA^a mod q = %ld,  Bob sends xB^a mod q = %ld\n", A, B);

    /* A possible key agreement: both learn the other's secret the same way, then K = xA*xB mod q */
    long inv = inverse(a, q - 1);
    long xA_found = power(A, inv, q), xB_found = power(B, inv, q);
    printf("Anyone (Eve too) computes a^-1 mod (q-1) = %ld\n", inv);
    printf("Eve finds secrets: xA = %ld, xB = %ld\n", xA_found, xB_found);
    printf("Key K = xA*xB mod q = %ld  -> Eve can compute the key as well.\n", xA_found * xB_found % q);
    printf("Conclusion: yes, Eve can find the secret numbers, so the scheme is insecure.\n");
    return 0;
}
