#include <stdio.h>

int fast_pow(int, int); // быстрое возведение в степень

int main() {
    int n = 0; int a = 0;
    scanf("%d%d", &a, &n); // считываем число и степень
    printf("%d", fast_pow(a, n)); // печатаем результат
    return 0;
}

// быстрое возведение в степень
int fast_pow(int a, int n) {
    if(n == 0) {
        return 1;
    }
    if(n == 1) {
        return a;
    }
    else {
        long ans = 0;
        if(n % 2 == 0) {
            ans = fast_pow(a * a, n / 2);
        }
        else {
            ans = a*fast_pow(a * a, (n - 1) / 2);
        }
        return ans;
    }

}
