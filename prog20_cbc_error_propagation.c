/* 20. Error propagation in CBC mode (DES used as the block cipher).
   a) Error in C1 corrupts P1 and P2 only. b) Error in P1 changes every ciphertext block
   after it, but the receiver still decrypts correctly (the errors cancel out). */
#include <string.h>
#include "des.h"

u64 toblock(const char *s) { u64 v = 0; for (int i = 0; i < 8; i++) v = (v << 8) | (unsigned char)s[i]; return v; }

void cbc_enc(u64 *p, u64 *c, u64 iv, u64 *k, int n) {
    u64 prev = iv;
    for (int i = 0; i < n; i++) { c[i] = des_block(p[i] ^ prev, k, 0); prev = c[i]; }
}
void cbc_dec(u64 *c, u64 *p, u64 iv, u64 *k, int n) {
    u64 prev = iv;
    for (int i = 0; i < n; i++) { p[i] = des_block(c[i], k, 1) ^ prev; prev = c[i]; }
}

int main() {
    u64 k[16], iv = 0xAABBCCDDEEFF0011ULL, P[4], C[4], D[4];
    const char *text = "BLOCK-01BLOCK-02BLOCK-03BLOCK-04";
    int i;
    des_keys(0x133457799BBCDFF1ULL, k);
    for (i = 0; i < 4; i++) P[i] = toblock(text + 8 * i);
    cbc_enc(P, C, iv, k, 4);

    printf("a) Flip 1 bit in transmitted C1, then decrypt:\n");
    C[0] ^= 1;
    cbc_dec(C, D, iv, k, 4);
    for (i = 0; i < 4; i++)
        printf("   P%d %s (differs in %d bits)\n", i + 1, D[i] == P[i] ? "correct" : "CORRUPTED",
               __builtin_popcountll(D[i] ^ P[i]));
    printf("   => only P1 and P2 are affected, P3 and later are fine.\n\n");

    printf("b) Flip 1 bit in source P1 before encryption:\n");
    u64 Q[4], C2[4], oldC[4];
    cbc_enc(P, oldC, iv, k, 4);
    memcpy(Q, P, sizeof P);
    Q[0] ^= 1;
    cbc_enc(Q, C2, iv, k, 4);
    for (i = 0; i < 4; i++) printf("   C%d %s\n", i + 1, C2[i] == oldC[i] ? "same" : "changed");
    cbc_dec(C2, D, iv, k, 4);
    for (i = 0; i < 4; i++)
        printf("   Receiver P%d: %s\n", i + 1, D[i] == Q[i] ? "decrypts to what was sent" : "wrong");
    printf("   => error propagates through ALL following ciphertext blocks, but only P1 is wrong at the receiver.\n");
    return 0;
}
