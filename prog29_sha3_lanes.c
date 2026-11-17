/* 29. SHA-3 with block (rate) size 1024 bits: 16 lanes of 64 bits are rate, 9 lanes are capacity.
   Starting with capacity lanes all zero, see how many rounds until every lane is non-zero.
   Only theta (column parity mixing) is needed to track this; permutation is ignored. */
#include <stdio.h>

int main() {
    int nz[5][5], x, y, round = 0;       /* nz[x][y] = lane has at least one nonzero bit */
    for (y = 0; y < 5; y++)
        for (x = 0; x < 5; x++)
            nz[x][y] = (x + 5 * y) < 16;     /* lanes 0..15 hold message block P0 */

    for (;;) {
        int all = 1;
        printf("After round %d:\n", round);
        for (y = 0; y < 5; y++) {
            for (x = 0; x < 5; x++) { printf("%d ", nz[x][y]); if (!nz[x][y]) all = 0; }
            printf("\n");
        }
        if (all) { printf("All lanes non-zero after %d round(s).\n", round); break; }

        int col[5], nw[5][5];                /* theta: lane gets XOR of neighbouring column parities */
        for (x = 0; x < 5; x++) { col[x] = 0; for (y = 0; y < 5; y++) col[x] |= nz[x][y]; }
        for (x = 0; x < 5; x++)
            for (y = 0; y < 5; y++)
                nw[x][y] = nz[x][y] | col[(x + 4) % 5] | col[(x + 1) % 5];
        for (x = 0; x < 5; x++) for (y = 0; y < 5; y++) nz[x][y] = nw[x][y];
        round++;
    }
    return 0;
}
