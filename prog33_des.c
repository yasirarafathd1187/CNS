/* 33. DES: 64-bit block, 56-bit key, 16 rounds. Same algorithm for encryption and decryption
   (round keys used in reverse order). All tables and the round function are in des.h.
   Test: key 133457799BBCDFF1, plaintext 0123456789ABCDEF -> ciphertext 85E813540F0AB405 */
#include "des.h"

int main() {
    u64 key, plain, cipher, sk[16];
    printf("Enter 64-bit key in hex   (e.g. 133457799BBCDFF1): ");
    scanf("%llx", &key);
    printf("Enter 64-bit plaintext hex (e.g. 0123456789ABCDEF): ");
    scanf("%llx", &plain);

    des_keys(key, sk);
    for (int i = 0; i < 16; i++) printf("K%-2d = %012llX\n", i + 1, sk[i]);

    cipher = des_block(plain, sk, 0);
    printf("Ciphertext: %016llX\n", cipher);
    printf("Decrypted : %016llX\n", des_block(cipher, sk, 1));
    return 0;
}
