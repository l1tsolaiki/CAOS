#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char const *argv[]) {
    int ch;
    int sum = 0;
    while ((ch = getchar_unlocked()) != EOF) {
        if (isdigit(ch)) {
            sum += ch - (int)'0';
        }
    }
    printf("%d\n", sum);
    return 0;
}
