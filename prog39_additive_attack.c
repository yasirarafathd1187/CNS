/* 39 (same as the earlier question). Letter-frequency attack on an additive (Caesar) cipher.
   All 26 shifts are tried and ranked by how English-like they are. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* English letter frequencies (%) a..z */
double freq[26] = {8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.15,0.77,4.0,2.4,
                   6.7,7.5,1.9,0.1,6.0,6.3,9.1,2.8,1.0,2.4,0.15,2.0,0.07};

int main() {
    char c[500], plain[26][500];
    double score[26];
    int order[26], top, i, k;

    printf("Enter ciphertext: ");
    fgets(c, sizeof c, stdin);
    c[strcspn(c, "\n")] = 0;
    printf("How many top plaintexts? ");
    scanf("%d", &top);

    for (k = 0; k < 26; k++) {
        score[k] = 0;
        for (i = 0; c[i]; i++) {
            if (isalpha(c[i])) {
                int p = (tolower(c[i]) - 'a' - k + 26) % 26;
                plain[k][i] = p + 'a';
                score[k] += freq[p];
            } else plain[k][i] = c[i];
        }
        plain[k][i] = 0;
        order[k] = k;
    }
    /* sort keys by score (highest first) */
    for (i = 0; i < 25; i++)
        for (k = 0; k < 25 - i; k++)
            if (score[order[k]] < score[order[k + 1]]) { int t = order[k]; order[k] = order[k + 1]; order[k + 1] = t; }

    if (top > 26) top = 26;
    for (i = 0; i < top; i++)
        printf("%2d) key=%2d score=%.1f  %s\n", i + 1, order[i], score[order[i]], plain[order[i]]);
    return 0;
}
