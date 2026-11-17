/* 8. Monoalphabetic cipher using a keyword (e.g. CIPHER):
   keyword followed by unused letters in normal order. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[50], cipherAlpha[27], text[200];
    int used[26] = {0}, n = 0;
    printf("Enter keyword (e.g. CIPHER): ");
    scanf("%49s", key);
    getchar();
    for (int i = 0; key[i]; i++) {
        int c = toupper(key[i]) - 'A';
        if (c >= 0 && c < 26 && !used[c]) { used[c] = 1; cipherAlpha[n++] = 'A' + c; }
    }
    for (int c = 0; c < 26; c++) if (!used[c]) cipherAlpha[n++] = 'A' + c;
    cipherAlpha[26] = 0;

    printf("plain : abcdefghijklmnopqrstuvwxyz\n");
    printf("cipher: ");
    for (int i = 0; i < 26; i++) printf("%c", tolower(cipherAlpha[i]));
    printf("\n");

    printf("Enter plaintext (lowercase): ");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = 0;

    char c[200], d[200];
    int i, j;
    for (i = 0; text[i]; i++) c[i] = islower(text[i]) ? cipherAlpha[text[i] - 'a'] : text[i];
    c[i] = 0;
    printf("Ciphertext: %s\n", c);
    for (i = 0; c[i]; i++) {
        d[i] = c[i];
        if (isupper(c[i]))
            for (j = 0; j < 26; j++) if (cipherAlpha[j] == c[i]) d[i] = 'a' + j;
    }
    d[i] = 0;
    printf("Decrypted : %s\n", d);
    return 0;
}
