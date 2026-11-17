/* 6. Break an affine cipher: most frequent ciphertext letter B, second U.
   Assume B -> e (4) and U -> t (19). Solve  4a+b = 1  and  19a+b = 20 (mod 26). */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    int a, b, A = 0, B = 0;
    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) != 1) continue;
        for (b = 0; b < 26; b++)
            if ((4 * a + b) % 26 == 1 && (19 * a + b) % 26 == 20) { A = a; B = b; }
    }
    printf("Key found: a = %d, b = %d\n", A, B);
    printf("Encryption: C = (%d p + %d) mod 26\n", A, B);

    int ainv = 0;
    for (int i = 1; i < 26; i++) if ((A * i) % 26 == 1) ainv = i;
    printf("Decryption: p = %d (C - %d) mod 26\n", ainv, B);

    char c[300];
    printf("Enter ciphertext to decrypt (lowercase/uppercase): ");
    fgets(c, sizeof c, stdin);
    printf("Plaintext: ");
    for (int i = 0; c[i] && c[i] != '\n'; i++) {
        if (isalpha(c[i])) printf("%c", (ainv * (tolower(c[i]) - 'a' - B + 26)) % 26 + 'a');
        else printf("%c", c[i]);
    }
    printf("\n");
    return 0;
}
