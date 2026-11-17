/* 11. How many keys does the Playfair cipher have? */
#include <stdio.h>

/* number of times x can be halved = approx log2(x) */
int log2approx(double x) { int n = 0; while (x >= 2) { x /= 2; n++; } return x >= 1.414 ? n + 1 : n; }

int main() {
    double f = 1;
    for (int i = 2; i <= 25; i++) f *= i;          /* 25! */
    printf("Possible keys = 25! = %.3e  ~ 2^%d\n", f, log2approx(f));

    /* a) The matrix can be shifted cyclically: 5 row shifts x 5 column shifts = 25
          arrangements give the same encryption, so divide by 25 -> 24! */
    double g = f / 25;
    printf("Effectively unique keys = 25!/25 = 24! = %.3e ~ 2^%d\n", g, log2approx(g));
    return 0;
}
