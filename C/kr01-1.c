#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    float x, y;
    scanf("%g%g", &x, &y);

    if (x >= 2 && 5 >= x && y >= 1 && 7 >= y) {
        if (y <= x + 3 && y >= x - 2) {
            printf("%d\n", 1);
        } else {
            printf("%d\n", 0);
        }
    } else {
        printf("%d\n", 0);
    }
    return 0;
}
