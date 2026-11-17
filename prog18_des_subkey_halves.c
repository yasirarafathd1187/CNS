/* 18. In DES the first 24 bits of each subkey come from the 28-bit C half and
   the second 24 bits come from the 28-bit D half (disjoint subsets). Shown using PC-2. */
#include "des.h"

int main() {
    int usedC[29] = {0}, usedD[29] = {0}, i;
    for (i = 0; i < 48; i++) {
        if (i < 24) usedC[PC2[i]] = 1;        /* positions 1..28  = C */
        else        usedD[PC2[i] - 28] = 1;   /* positions 29..56 = D */
    }
    printf("First 24 bits of PC-2 pick from C positions: ");
    for (i = 1; i <= 28; i++) if (usedC[i]) printf("%d ", i);
    printf("\nBits of C not used: ");
    for (i = 1; i <= 28; i++) if (!usedC[i]) printf("%d ", i);
    printf("\nLast 24 bits of PC-2 pick from D positions: ");
    for (i = 1; i <= 28; i++) if (usedD[i]) printf("%d ", i);
    printf("\nBits of D not used: ");
    for (i = 1; i <= 28; i++) if (!usedD[i]) printf("%d ", i);

    int ok = 1;
    for (i = 0; i < 24; i++) if (PC2[i] > 28) ok = 0;
    for (i = 24; i < 48; i++) if (PC2[i] <= 28) ok = 0;
    printf("\n\nFirst 24 from C only and last 24 from D only: %s\n\n", ok ? "TRUE" : "FALSE");

    u64 sk[16];
    des_keys(0x133457799BBCDFF1ULL, sk);
    for (i = 0; i < 16; i++)
        printf("K%-2d = %06llX | %06llX   (C-part | D-part)\n", i + 1, sk[i] >> 24, sk[i] & 0xFFFFFF);
    return 0;
}
