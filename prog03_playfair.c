/* 3. Playfair cipher: 5x5 matrix built from a keyword, encrypts two letters at a time */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char m[5][5];

/* build 5x5 matrix from keyword (I and J share a cell) */
void build(const char *key) {
    int used[26] = {0}, n = 0;
    char all[100];
    for (int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';
        if (isalpha(c) && !used[c - 'A']) { used[c - 'A'] = 1; all[n++] = c; }
    }
    for (char c = 'A'; c <= 'Z'; c++)
        if (c != 'J' && !used[c - 'A']) all[n++] = c;
    for (int i = 0; i < 25; i++) m[i / 5][i % 5] = all[i];
}

void find(char c, int *r, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == c) { *r = i; *col = j; }
}

/* dir = 1 encrypt, dir = 4 decrypt (same as -1 mod 5) */
void pair(char a, char b, int dir, char *x, char *y) {
    int r1, c1, r2, c2;
    find(a, &r1, &c1); find(b, &r2, &c2);
    if (r1 == r2)      { *x = m[r1][(c1 + dir) % 5]; *y = m[r2][(c2 + dir) % 5]; }
    else if (c1 == c2) { *x = m[(r1 + dir) % 5][c1]; *y = m[(r2 + dir) % 5][c2]; }
    else               { *x = m[r1][c2];             *y = m[r2][c1]; }
}

/* keep letters only, J->I, put X between double letters, pad with X */
void prepare(const char *in, char *out) {
    int n = 0;
    for (int i = 0; in[i]; i++) {
        if (!isalpha(in[i])) continue;
        char c = toupper(in[i]);
        if (c == 'J') c = 'I';
        if (n % 2 == 1 && out[n - 1] == c) out[n++] = 'X';
        out[n++] = c;
    }
    if (n % 2) out[n++] = 'X';
    out[n] = 0;
}

void process(const char *in, char *out, int dir) {
    int n = strlen(in);
    for (int i = 0; i < n; i += 2) pair(in[i], in[i + 1], dir, &out[i], &out[i + 1]);
    out[n] = 0;
}

void show() {
    printf("Playfair matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) printf("%c ", m[i][j]);
        printf("\n");
    }
}

int main() {
    char key[50], text[200], p[400], c[400], d[400];
    printf("Enter keyword: ");
    scanf("%49s", key);
    getchar();
    printf("Enter plaintext: ");
    fgets(text, sizeof text, stdin);

    build(key);
    show();
    prepare(text, p);
    process(p, c, 1);
    process(c, d, 4);
    printf("Prepared text: %s\nCiphertext   : %s\nDecrypted    : %s\n", p, c, d);
    return 0;
}
