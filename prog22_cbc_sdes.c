/* 22. CBC mode with S-DES.  IV = 1010 1010, key = 01111 11101
   plaintext 0000 0001 0010 0011  ->  ciphertext should be 1111 0100 0000 1011 */
#include <stdio.h>
/* S-DES (Simplified DES) - 8-bit block, 10-bit key */
static const int P10[10] = {3,5,2,7,4,10,1,9,8,6};
static const int P8[8]   = {6,3,7,4,8,5,10,9};
static const int IPS[8]  = {2,6,3,1,4,8,5,7};
static const int IPI[8]  = {4,1,3,5,7,2,8,6};
static const int EP[8]   = {4,1,2,3,2,3,4,1};
static const int P4[4]   = {2,4,3,1};
static const int S0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
static const int S1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

int perm(int in, const int *t, int n, int inbits) {
    int out = 0;
    for (int i = 0; i < n; i++) out = (out << 1) | ((in >> (inbits - t[i])) & 1);
    return out;
}
void sdes_keys(int key, int *k1, int *k2) {
    int p = perm(key, P10, 10, 10), l = p >> 5, r = p & 31;
    l = ((l << 1) | (l >> 4)) & 31;  r = ((r << 1) | (r >> 4)) & 31;       /* LS-1 */
    *k1 = perm((l << 5) | r, P8, 8, 10);
    l = ((l << 2) | (l >> 3)) & 31;  r = ((r << 2) | (r >> 3)) & 31;       /* LS-2 */
    *k2 = perm((l << 5) | r, P8, 8, 10);
}
int fk(int b, int k) {
    int l = b >> 4, r = b & 15;
    int e = perm(r, EP, 8, 4) ^ k, a = e >> 4, c = e & 15;
    int s0 = S0[((a & 8) >> 2) | (a & 1)][(a >> 1) & 3];
    int s1 = S1[((c & 8) >> 2) | (c & 1)][(c >> 1) & 3];
    int p = perm((s0 << 2) | s1, P4, 4, 4);
    return ((l ^ p) << 4) | r;
}
int sdes(int b, int k1, int k2, int dec) {          /* dec=1 swaps key order */
    if (dec) { int t = k1; k1 = k2; k2 = t; }
    b = perm(b, IPS, 8, 8);
    b = fk(b, k1);
    b = ((b & 15) << 4) | (b >> 4);
    b = fk(b, k2);
    return perm(b, IPI, 8, 8);
}
void bin8(int v) { for (int i = 7; i >= 0; i--) { printf("%d", (v >> i) & 1); if (i == 4) printf(" "); } }

int main() {
    int key = 0x1FD;                 /* 01111 11101 */
    int iv = 0xAA;                   /* 1010 1010   */
    int p[2] = {0x01, 0x23};         /* 0000 0001, 0010 0011 */
    int c[2], d[2], k1, k2, prev = iv;
    sdes_keys(key, &k1, &k2);

    for (int i = 0; i < 2; i++) {
        c[i] = sdes(p[i] ^ prev, k1, k2, 0);       /* C_i = E(P_i xor C_(i-1)) */
        prev = c[i];
    }
    printf("Ciphertext: "); bin8(c[0]); printf(" "); bin8(c[1]); printf("\n");

    prev = iv;
    for (int i = 0; i < 2; i++) {
        d[i] = sdes(c[i], k1, k2, 1) ^ prev;       /* P_i = D(C_i) xor C_(i-1) */
        prev = c[i];
    }
    printf("Decrypted : "); bin8(d[0]); printf(" "); bin8(d[1]); printf("\n");
    return 0;
}
