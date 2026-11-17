/* 34 (same as the earlier question). Padding for ECB/CBC/CFB: add a 1 bit followed by 0 bits (byte form: 0x80 00 00 ...).
   Why pad even when the message is already a full block? Otherwise the receiver cannot tell
   whether the last block contains padding or real data. */
#include <stdio.h>
#include <string.h>

#define BS 8   /* block size in bytes */

int pad(const unsigned char *in, int len, unsigned char *out, int always) {
    memcpy(out, in, len);
    int n = len;
    if (always || len % BS) {            /* always = 1 : pad every message */
        out[n++] = 0x80;
        while (n % BS) out[n++] = 0x00;
    }
    return n;
}

int unpad(unsigned char *in, int len) {   /* remove 0x00s then the 0x80 */
    while (len > 0 && in[len - 1] == 0x00) len--;
    if (len > 0 && in[len - 1] == 0x80) len--;
    return len;
}

void show(const char *name, unsigned char *b, int n) {
    printf("%-22s", name);
    for (int i = 0; i < n; i++) { printf("%02X ", b[i]); if (i % BS == BS - 1) printf("| "); }
    printf("\n");
}

int main() {
    unsigned char out[64], msg1[] = "HELLO", msg2[] = "12345678";
    int n;

    n = pad(msg1, 5, out, 1);  show("\"HELLO\" padded:", out, n);
    n = pad(msg2, 8, out, 1);  show("\"12345678\" padded:", out, n);
    printf("   -> complete block still gets an extra full padding block.\n\n");

    /* what goes wrong if full blocks are NOT padded */
    unsigned char tricky[8] = {'A','B','C','D','E','F','G',0x80};   /* real data that ends in 0x80 */
    n = pad(tricky, 8, out, 0);
    int back = unpad(out, n);
    printf("Without padding a full block: original length 8, receiver removes padding and gets length %d  (WRONG)\n", back);
    n = pad(tricky, 8, out, 1);
    back = unpad(out, n);
    printf("With an extra padding block : original length 8, receiver gets length %d  (CORRECT)\n", back);
    return 0;
}
