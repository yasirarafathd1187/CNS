/* 16. Letter-frequency attack on a monoalphabetic substitution cipher.
   1. Rank cipher letters by frequency and match them with English order "etaoinshrdlcumwfgypbvkjxqz".
   2. Create more guesses by swapping neighbouring letters in that ranking.
   3. Score every guess by counting common English digraphs/trigraphs and show the best ones. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXC 26
const char *english = "etaoinshrdlcumwfgypbvkjxqz";
const char *common[] = {"th","he","in","er","an","re","on","at","en","nd","the","and","ing","ion","ent"};

char cipher[1000];
char guess[MAXC + 1][27];     /* mapping: guess[g][cipher letter] = plain letter */
char text[MAXC + 1][1000];
int  score[MAXC + 1], order[MAXC + 1];

int count(const char *s, const char *w) {
    int n = 0, L = strlen(w);
    for (; *s; s++) if (strncmp(s, w, L) == 0) n++;
    return n;
}

int main() {
    int freq[26] = {0}, rank[26], i, j, g, top;

    printf("Enter ciphertext (letters): ");
    fgets(cipher, sizeof cipher, stdin);
    cipher[strcspn(cipher, "\n")] = 0;
    printf("How many top plaintexts? ");
    scanf("%d", &top);

    for (i = 0; cipher[i]; i++) if (isalpha(cipher[i])) { cipher[i] = tolower(cipher[i]); freq[cipher[i] - 'a']++; }
    for (i = 0; i < 26; i++) rank[i] = i;
    for (i = 0; i < 25; i++)                       /* sort letters by frequency */
        for (j = 0; j < 25 - i; j++)
            if (freq[rank[j]] < freq[rank[j + 1]]) { int t = rank[j]; rank[j] = rank[j + 1]; rank[j + 1] = t; }

    for (g = 0; g <= MAXC - 1; g++) {              /* guess 0 = straight match, guess g = swap ranks g-1,g */
        char map[26];
        for (i = 0; i < 26; i++) map[rank[i]] = english[i];
        if (g > 0) { char t = map[rank[g - 1]]; map[rank[g - 1]] = map[rank[g]]; map[rank[g]] = t; }
        for (i = 0; cipher[i]; i++) text[g][i] = isalpha(cipher[i]) ? map[cipher[i] - 'a'] : cipher[i];
        text[g][i] = 0;
        score[g] = 0;
        for (i = 0; i < 15; i++) score[g] += count(text[g], common[i]) * (int)strlen(common[i]);
        order[g] = g;
    }
    for (i = 0; i < MAXC - 1; i++)
        for (j = 0; j < MAXC - 1 - i; j++)
            if (score[order[j]] < score[order[j + 1]]) { int t = order[j]; order[j] = order[j + 1]; order[j + 1] = t; }

    if (top > MAXC) top = MAXC;
    for (i = 0; i < top; i++) printf("%2d) score=%3d  %s\n", i + 1, score[order[i]], text[order[i]]);
    return 0;
}
