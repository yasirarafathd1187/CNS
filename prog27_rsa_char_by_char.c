/* 27. RSA applied to each letter (A=0..Z=25) separately is NOT secure.
   Attack: only 26 possible plaintexts, so encrypt all 26 with the public key and compare
   (a dictionary / table look-up attack). */
#include <stdio.h>
#include <string.h>

long power(long b, long e, long m) { long r = 1; b %= m; while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; } return r; }

int main() {
    long n = 3599, e = 31;
    char msg[] = "HELLO";
    long c[20];
    int len = strlen(msg), i, j;

    printf("Alice encrypts each letter:  ");
    for (i = 0; i < len; i++) { c[i] = power(msg[i] - 'A', e, n); printf("%ld ", c[i]); }

    long table[26];                      /* Eve builds the table with the PUBLIC key */
    for (j = 0; j < 26; j++) table[j] = power(j, e, n);

    printf("\nEve recovers the message   : ");
    for (i = 0; i < len; i++)
        for (j = 0; j < 26; j++)
            if (table[j] == c[i]) printf("%c", 'A' + j);
    printf("\n");
    return 0;
}
