/* 17. DES decryption uses K16..K1. Key schedule for decryption:
   same PC-1, but shift RIGHT with schedule 0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 */
#include "des.h"

int main() {
    u64 key = 0x133457799BBCDFF1ULL, enc[16], dec[16];
    const int RS[16] = {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    des_keys(key, enc);

    u64 cd = permute(key, PC1, 56, 64);
    unsigned c = (cd >> 28) & 0xFFFFFFF, d = cd & 0xFFFFFFF;
    printf("Round  Decryption key       Equals K(17-round)?\n");
    for (int i = 0; i < 16; i++) {
        int s = RS[i];
        if (s) {
            c = ((c >> s) | (c << (28 - s))) & 0xFFFFFFF;
            d = ((d >> s) | (d << (28 - s))) & 0xFFFFFFF;
        }
        dec[i] = permute(((u64)c << 28) | d, PC2, 48, 56);
        printf("%2d     %012llX         %s\n", i + 1, dec[i], dec[i] == enc[15 - i] ? "yes" : "NO");
    }
    /* use the new schedule in the normal (encryption-order) direction to decrypt */
    u64 plain = 0x0123456789ABCDEFULL, cipher = des_block(plain, enc, 0);
    printf("\nPlaintext  : %016llX\nCiphertext : %016llX\nDecrypted  : %016llX\n",
           plain, cipher, des_block(cipher, dec, 0));
    return 0;
}
