#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int max1;
    int max2;
    scanf("%d%d", &max1, &max2);

    int ch;
    while (1 == scanf("%d", &ch)) {
        if (ch >= max1 && ch >= max2 && max1 >= max2) {
            max2 = ch;
        } else if (ch >= max1 && ch >= max2 && max2 >= max1) {
            max1 = ch;
        } else if (max1 <= ch && ch <= max2) {
            max1 = ch;
        } else if (max2 <= ch && ch <= max1) {
            max2 = ch;
        }
    }

    long maximum = max1 * max2;
    printf("%ld\n", maximum);
    return 0;
}
