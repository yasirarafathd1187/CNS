/* 24. RSA: public key e = 31, n = 3599. Find the private key d. */
#include <stdio.h>

/* extended Euclid: returns inverse of a mod m */
long inverse(long a, long m) {
    long m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        long q = a / m, t = m;
        m = a % m; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    return x1 < 0 ? x1 + m0 : x1;
}

int main() {
    long e = 31, n = 3599, p = 0, q;
    for (long i = 2; i * i <= n; i++)         /* trial and error to find p and q */
        if (n % i == 0) { p = i; break; }
    q = n / p;
    long phi = (p - 1) * (q - 1);
    long d = inverse(e, phi);
    printf("p = %ld, q = %ld\nphi(n) = %ld\n", p, q, phi);
    printf("Private key d = %ld  (check: e*d mod phi = %ld)\n", d, (e * d) % phi);
    return 0;
}
