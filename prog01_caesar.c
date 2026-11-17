/* 1. Caesar cipher: shift every letter by k (1-25) */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void shift(char *s, int k) {
    for (int i = 0; s[i]; i++) {
        if (isupper(s[i])) s[i] = (s[i] - 'A' + k) % 26 + 'A';
        else if (islower(s[i])) s[i] = (s[i] - 'a' + k) % 26 + 'a';
    }
}

int main() {
    char text[200];
    int k;
    printf("Enter plaintext: ");
    fgets(text, sizeof text, stdin);
    text[strcspn(text, "\n")] = 0;
    printf("Enter key k (1-25): ");
    scanf("%d", &k);

    shift(text, k);
    printf("Ciphertext : %s\n", text);
    shift(text, 26 - k);
    printf("Decrypted  : %s\n", text);
    return 0;
}
