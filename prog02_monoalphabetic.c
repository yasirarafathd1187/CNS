/* 2. Monoalphabetic substitution cipher: each letter maps to one unique letter */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[27], text[200];
    printf("Enter 26-letter key (a permutation of a-z, e.g. qwertyuiopasdfghjklzxcvbnm): ");
    scanf("%26s", key);
    getchar();
    printf("Enter plaintext (lowercase): ");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = 0;

    char cipher[200];
    int i, j;
    for (i = 0; text[i]; i++)
        cipher[i] = islower(text[i]) ? tolower(key[text[i] - 'a']) : text[i];
    cipher[i] = 0;
    printf("Ciphertext: %s\n", cipher);

    for (i = 0; cipher[i]; i++) {
        char c = cipher[i];
        if (islower(c)) {
            for (j = 0; j < 26; j++)
                if (tolower(key[j]) == c) { c = 'a' + j; break; }
        }
        text[i] = c;
    }
    printf("Decrypted : %s\n", text);
    return 0;
}
