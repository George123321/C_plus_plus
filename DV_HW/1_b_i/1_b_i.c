#include <stdio.h>

int shift(int [], int, int); /* перестановка (делает несколько раз циклический сдвиг) */
int cyclic_shift(int [], int); /* циклический сдвиг */

int main() {
    int n = 0;
    printf("Write the number of items:\n");
    scanf("%d", &n);

    int a[n];
    printf("Write items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d ", &a[i]);
    }

    int m = 0;
    printf("Write number m:\n");
    scanf("%d", &m);

    shift(a, m, n);

    printf("Your new array is:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}

/* сделаем циклический сдвиг n - m - 1 раз */
int shift(int a[], int m, int n) {
    for (int i = 0; i <= n - m - 1; i++) {
        cyclic_shift(a, n);
    }
    return *a;
}

/* циклический сдвиг */
int cyclic_shift(int a[], int n) {
    int tmp = 0, i = 0;
    /* будем передвигать последний элемент массива вперед */
    while ((i < n) && (n - i - 2 >= 0)) {
        tmp = a[n - i - 1];
        a[n - i - 1] = a[n - i - 2];
        a[n - i - 2] = tmp;
        i++;
    }
    return *a;
}