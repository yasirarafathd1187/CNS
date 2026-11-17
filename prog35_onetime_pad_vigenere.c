/* 35 (same as the earlier question). One-time pad version of Vigenere: key is a stream of numbers 0-25 */
#include <stdio.h>
#include <string.h>

int main() {
    /* a) encrypt "sendmoremoney" with the key stream */
    char plain[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int n = strlen(plain), i;
    char cipher[50];

    for (i = 0; i < n; i++) cipher[i] = (plain[i] - 'a' + key[i]) % 26 + 'a';
    cipher[n] = 0;
    printf("a) Plaintext : %s\n   Ciphertext: %s\n", plain, cipher);

    /* b) find a key so the same ciphertext decrypts to "cashnotneeded": k = c - p */
    char fake[] = "cashnotneeded";
    printf("b) Key for \"%s\": ", fake);
    for (i = 0; i < n; i++) printf("%d ", ((cipher[i] - fake[i]) % 26 + 26) % 26);
    printf("\n");
    return 0;
}
