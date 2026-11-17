/* 12. Hill cipher (2x2) with key [9 4; 5 7].
   Encrypt "meet me at the usual place at ten rather than eight oclock" and decrypt. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int inverse(int a) { for (int i = 1; i < 26; i++) if ((a * i) % 26 == 1) return i; return -1; }

int main() {
    int K[2][2] = {{9, 4}, {5, 7}};
    char text[] = "meet me at the usual place at ten rather than eight oclock";
    char p[200], c[200], d[200];
    int n = 0, i;

    for (i = 0; text[i]; i++) if (isalpha(text[i])) p[n++] = tolower(text[i]);
    if (n % 2) p[n++] = 'x';                    /* pad */
    p[n] = 0;
    printf("Plaintext : %s\n\nEncryption (C = K * P mod 26):\n", p);

    for (i = 0; i < n; i += 2) {
        int p1 = p[i] - 'a', p2 = p[i + 1] - 'a';
        int c1 = (K[0][0] * p1 + K[0][1] * p2) % 26;
        int c2 = (K[1][0] * p1 + K[1][1] * p2) % 26;
        printf("%c%c = (%d,%d) -> (9*%d+4*%d, 5*%d+7*%d) mod 26 = (%d,%d) -> %c%c\n",
               p[i], p[i+1], p1, p2, p1, p2, p1, p2, c1, c2, c1 + 'A', c2 + 'A');
        c[i] = c1 + 'A'; c[i + 1] = c2 + 'A';
    }
    c[n] = 0;
    printf("Ciphertext: %s\n\n", c);

    /* inverse key = det^-1 * [7 -4; -5 9] mod 26 */
    int det = ((K[0][0] * K[1][1] - K[0][1] * K[1][0]) % 26 + 26) % 26;
    int di = inverse(det);
    int Ki[2][2] = {{(di * K[1][1]) % 26, (di * (26 - K[0][1])) % 26},
                    {(di * (26 - K[1][0])) % 26, (di * K[0][0]) % 26}};
    printf("det = %d, det^-1 = %d\nInverse key = [%d %d; %d %d]\n\nDecryption:\n",
           det, di, Ki[0][0], Ki[0][1], Ki[1][0], Ki[1][1]);
    for (i = 0; i < n; i += 2) {
        int c1 = c[i] - 'A', c2 = c[i + 1] - 'A';
        int p1 = (Ki[0][0] * c1 + Ki[0][1] * c2) % 26;
        int p2 = (Ki[1][0] * c1 + Ki[1][1] * c2) % 26;
        d[i] = p1 + 'a'; d[i + 1] = p2 + 'a';
        printf("%c%c -> %c%c\n", c[i], c[i+1], d[i], d[i+1]);
    }
    d[n] = 0;
    printf("Recovered plaintext: %s\n", d);
    return 0;
}
