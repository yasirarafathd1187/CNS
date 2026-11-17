/* 4. Polyalphabetic substitution (Vigenere): key letters decide the shift of each plaintext letter */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[50], text[200], c[200], d[200];
    printf("Enter key (letters): ");
    scanf("%49s", key);
    getchar();
    printf("Enter plaintext (letters only): ");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = 0;

    int kl = strlen(key), n = 0;
    for (int i = 0; text[i]; i++) {
        if (!isalpha(text[i])) continue;
        int p = tolower(text[i]) - 'a';
        int k = tolower(key[n % kl]) - 'a';
        c[n] = (p + k) % 26 + 'a';
        n++;
    }
    c[n] = 0;
    printf("Ciphertext: %s\n", c);

    for (int i = 0; i < n; i++) {
        int k = tolower(key[i % kl]) - 'a';
        d[i] = (c[i] - 'a' - k + 26) % 26 + 'a';
    }
    d[n] = 0;
    printf("Decrypted : %s\n", d);
    return 0;
}
