/* 19. CBC encryption/decryption using 3DES (E-D-E with three keys).
   a) For security choose 3DES (168-bit key, DES alone has only 56 bits).
   b) For performance choose DES (3DES is about 3 times slower). */
#include <string.h>
#include "des.h"

u64 tdes(u64 b, u64 k1[], u64 k2[], u64 k3[], int dec) {
    if (!dec) return des_block(des_block(des_block(b, k1, 0), k2, 1), k3, 0);
    return des_block(des_block(des_block(b, k3, 1), k2, 0), k1, 1);
}
u64 toblock(const char *s) { u64 v = 0; for (int i = 0; i < 8; i++) v = (v << 8) | (unsigned char)s[i]; return v; }

int main() {
    u64 k1[16], k2[16], k3[16];
    des_keys(0x0123456789ABCDEFULL, k1);
    des_keys(0x23456789ABCDEF01ULL, k2);
    des_keys(0x456789ABCDEF0123ULL, k3);
    u64 iv = 0x1122334455667788ULL;

    char msg[65];
    printf("Enter message (max 64 chars): ");
    fgets(msg, sizeof msg, stdin);
    msg[strcspn(msg, "\n")] = 0;
    int len = strlen(msg);
    while (len % 8) msg[len++] = ' ';           /* pad with spaces */
    msg[len] = 0;
    int nb = len / 8;
    u64 c[8], prev = iv;

    printf("Ciphertext blocks:\n");
    for (int i = 0; i < nb; i++) {
        c[i] = tdes(toblock(msg + 8 * i) ^ prev, k1, k2, k3, 0);
        prev = c[i];
        printf("  C%d = %016llX\n", i + 1, c[i]);
    }
    prev = iv;
    printf("Decrypted: ");
    for (int i = 0; i < nb; i++) {
        u64 p = tdes(c[i], k1, k2, k3, 1) ^ prev;
        prev = c[i];
        for (int j = 7; j >= 0; j--) printf("%c", (int)((p >> (8 * j)) & 0xFF));
    }
    printf("\n");
    return 0;
}
