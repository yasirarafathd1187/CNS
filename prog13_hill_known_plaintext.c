/* 13. Known plaintext attack on a 2x2 Hill cipher.
   Using two plaintext/ciphertext digraphs:  C = K P  =>  K = C * P^-1 (mod 26)
   Example: plaintext "help" -> ciphertext "BLDE"  (key was [9 4; 5 7]) */
#include <stdio.h>
#include <ctype.h>

int inverse(int a) { for (int i = 1; i < 26; i++) if ((a * i) % 26 == 1) return i; return -1; }
int mod(int x) { return ((x % 26) + 26) % 26; }

int main() {
    char p[10], c[10];
    printf("Enter 4 plaintext letters  (e.g. help): ");
    scanf("%4s", p);
    printf("Enter 4 ciphertext letters (e.g. BLDE): ");
    scanf("%4s", c);

    /* columns of P and C are the two digraphs */
    int P[2][2] = {{tolower(p[0]) - 'a', tolower(p[2]) - 'a'}, {tolower(p[1]) - 'a', tolower(p[3]) - 'a'}};
    int C[2][2] = {{tolower(c[0]) - 'a', tolower(c[2]) - 'a'}, {tolower(c[1]) - 'a', tolower(c[3]) - 'a'}};

    int det = mod(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int di = inverse(det);
    if (di < 0) { printf("P is not invertible mod 26, choose other plaintext pairs.\n"); return 0; }

    int Pi[2][2] = {{mod(di * P[1][1]), mod(-di * P[0][1])}, {mod(-di * P[1][0]), mod(di * P[0][0])}};
    int K[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            K[i][j] = mod(C[i][0] * Pi[0][j] + C[i][1] * Pi[1][j]);

    printf("Recovered key K =\n  %d %d\n  %d %d\n", K[0][0], K[0][1], K[1][0], K[1][1]);
    return 0;
}
