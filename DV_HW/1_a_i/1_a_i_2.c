#include <stdio.h>

void vsv(int); // функция, которая рекурсивно печатает число наоборот

int main() {
    int a = 0;
    scanf("%d", &a);

    vsv(a);
    return 0;
}

void vsv(int x) {
    if(x < 10) {
        printf("%d", x);
    }
    else {
        printf("%d", x % 10);
        vsv(x / 10);
    }

}