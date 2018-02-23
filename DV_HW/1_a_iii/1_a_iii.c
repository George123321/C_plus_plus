#include <stdio.h>

/* задача о ханойских башнях*/
void hanoi(int, int, int, int);

int main() {
    int n = 0;
    scanf("%d", &n);
    hanoi(n, 1, 2, 3);
    return 0;
}

/* n - количество дисков, l - начальный столб, s - временный столб, t - конечный столб */
void hanoi(int n, int l, int s, int t) {
    /* если диск один - перекладываем его с 1 на 3 */
    if (n == 1) {
        printf("%d -> %d\n", l, t);
    }
    else {
        /* перемещаем n - 1 диск с 1 на 2 (временную) */
        hanoi(n - 1, l, t, s);
        /* перемещаем самый большой диск с 1 на 2 */
        printf("%d -> %d\n", l, t);
        /* перемещаем n - 1 диск с 3 на 2*/
        hanoi(n - 1, s, l, t);
    }

}