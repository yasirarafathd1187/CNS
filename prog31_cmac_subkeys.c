/* 31. CMAC subkey generation:  L = E(K, 0...0);  K1 = L<<1 (xor Cb if MSB(L)=1);  K2 = K1<<1 (xor Cb if MSB(K1)=1)
   a) constants: Cb = 0x1B for 64-bit blocks, Cb = 0x87 for 128-bit blocks
      (low bits of the polynomial x^64+x^4+x^3+x+1 and x^128+x^7+x^2+x+1).
   b) Left shift = multiplication by x in GF(2^b); the conditional XOR reduces the result modulo
      the polynomial when the MSB falls off. */
#include "des.h"

u64 dbl(u64 v) { return (v << 1) ^ ((v >> 63) ? 0x1B : 0); }

int main() {
    u64 k[16];
    des_keys(0x133457799BBCDFF1ULL, k);
    u64 L  = des_block(0, k, 0);        /* encrypt the all-zero block */
    u64 K1 = dbl(L), K2 = dbl(K1);
    printf("Constants: 64-bit block -> 0x1B,  128-bit block -> 0x87\n\n");
    printf("L  = E(K,0) = %016llX\nK1 = %016llX\nK2 = %016llX\n", L, K1, K2);
    return 0;
}
