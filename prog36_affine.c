/* 36 (same as the earlier question). Affine Caesar cipher: C = (a*p + b) mod 26 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    int a, b, i, ainv = 0;
    char text[200], c[200], d[200];

    printf("a) Limitation on b: none. b can be any value 0..25 (it is just a shift).\n");
    printf("b) Allowed a (gcd(a,26)=1): ");
    for (i = 1; i < 26; i++) if (gcd(i, 26) == 1) printf("%d ", i);
    printf("\n   Not allowed a: ");
    for (i = 1; i < 26; i++) if (gcd(i, 26) != 1) printf("%d ", i);
    printf("\n   (all even numbers and 13, because they share a factor with 26)\n\n");

    printf("Enter a and b: ");
    scanf("%d %d", &a, &b);
    if (gcd(a, 26) != 1) { printf("a = %d is not allowed (not one-to-one)\n", a); return 0; }
    for (i = 1; i < 26; i++) if ((a * i) % 26 == 1) ainv = i;
    getchar();
    printf("Enter plaintext (lowercase): ");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = 0;

    for (i = 0; text[i]; i++)
        c[i] = islower(text[i]) ? (a * (text[i] - 'a') + b) % 26 + 'a' : text[i];
    c[i] = 0;
    printf("Ciphertext: %s\n", c);
    for (i = 0; c[i]; i++)
        d[i] = islower(c[i]) ? (ainv * (c[i] - 'a' - b + 26)) % 26 + 'a' : c[i];
    d[i] = 0;
    printf("Decrypted : %s\n", d);
    return 0;
}
