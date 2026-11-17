/* 7. Decrypt the simple substitution cipher (Poe's "Gold Bug").
   Steps: 8 is the most common symbol -> e ; ;48 is the most common word -> "the".
   Then more words are deduced. The final symbol table is below. */
#include <stdio.h>
#include <string.h>

const char *sym[]  = {"5","3","‡","†","0",")","6","*",";","4","8","2",".","¶","]",":","(","9","?","—","1"};
const char  letter[] = "agodlsinthebpvwyrmucf";

int main() {
    const char *cipher =
    "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
    "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
    ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
    "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int n = sizeof(letter) - 1, count[30] = {0};

    /* frequency count of every symbol */
    for (const char *p = cipher; *p; ) {
        int k, hit = 0;
        for (k = 0; k < n; k++) {
            int L = strlen(sym[k]);
            if (strncmp(p, sym[k], L) == 0) { count[k]++; p += L; hit = 1; break; }
        }
        if (!hit) p++;
    }
    printf("Symbol frequencies:\n");
    for (int k = 0; k < n; k++) printf("  %-3s : %2d  -> %c\n", sym[k], count[k], letter[k]);

    printf("\nDecrypted message:\n");
    for (const char *p = cipher; *p; ) {
        int k, hit = 0;
        for (k = 0; k < n; k++) {
            int L = strlen(sym[k]);
            if (strncmp(p, sym[k], L) == 0) { putchar(letter[k]); p += L; hit = 1; break; }
        }
        if (!hit) { putchar(*p); p++; }
    }
    printf("\n");
    return 0;
}
