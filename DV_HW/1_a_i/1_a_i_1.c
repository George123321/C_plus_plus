#include <stdio.h>
#include <string.h>

void vsv(char *); // функция, которая рекурсивно печатает строку наоборот
int len_int(int); // вычисляет размер инта

int main() {
    int a = 0;
    scanf("%d", &a);

    char s[len_int(a)];
    sprintf(s, "%d", a);

    vsv(s);
    return 0;
}

int len_int(int a) {
    int ans = 0;
    while(a) {
        a = a/10;
        ans++;
    }
    return ans;
}

void vsv(char* s) {
    if(strlen(s) == 1) {
        printf(s);
    }
    else {
        vsv(&s[1]);
        printf("%c", s[0]);
    }
}