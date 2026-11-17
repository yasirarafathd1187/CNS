/* 30. CBC-MAC forgery: if T = MAC(K, X) for one block X, then the two-block message
   X || (X xor T) has the same MAC T.   (DES is used as block cipher) */
#include "des.h"

int main() {
    u64 k[16], X = 0x4142434445464748ULL;
    des_keys(0x133457799BBCDFF1ULL, k);

    u64 T = des_block(X, k, 0);                 /* MAC of one block */
    printf("X            = %016llX\nT = MAC(X)   = %016llX\n", X, T);

    u64 X2 = X ^ T;                             /* forged second block */
    u64 c1 = des_block(X, k, 0);                /* CBC-MAC of X || X2 */
    u64 c2 = des_block(c1 ^ X2, k, 0);
    printf("Forged message: %016llX || %016llX\nMAC of it    = %016llX\n", X, X2, c2);
    printf(c2 == T ? "Same MAC! Adversary forged a valid MAC without the key.\n" : "Different\n");
    return 0;
}
