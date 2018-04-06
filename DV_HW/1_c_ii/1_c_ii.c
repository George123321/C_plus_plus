#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include <string.h>
#include <ctype.h>

/* функция, которая проверяет наличие слова в массиве */
int is_in(char *str, char **str_array, int number_of_elements) {
    if (number_of_elements == 0) {
        return 0;
    }
    for (int i = 0; i < number_of_elements; i++) {
        if (strcmp(str, str_array[i]) == 0) { // если строки равны
            return 1;
        }
    }
    return 0;
}

void add_to_stack(const char *elem, struct Stack *st) {
    char binary_operations[5][2] = {"+", "-", "*", "/", "^"};
    char unar_operations[7][6] = {"sqrt", "sin", "cos", "tan", "ln", "log10", "exp"};

    if (isdigit(elem[0])) {
        double d = strtod(elem, NULL);
        stack_push(st, d);
    } else {
        // посмотрим, какая операция
        int type_of_binary_operation = -1;
        int type_of_unar_operation = -1;
        for (int i = 0; i < 5; i++) {
            if (strcmp(elem, binary_operations[i]) == 0) {
                type_of_binary_operation = i;

                double x = stack_pop(st);
                double y = stack_pop(st);
                switch (type_of_binary_operation) {
                    case 0:
                        stack_push(st, y + x);
                        break;
                    case 1:
                        stack_push(st, y - x);
                        break;
                    case 2:
                        stack_push(st, y * x);
                        break;
                    case 3:
                        if (x == 0) {
                            stack_push(st, NAN);
                            printf("Division by zero");
                            exit(0);
                        }
                        stack_push(st, y / x);
                        break;
                    case 4:
                        if (y <= 0) {
                            if (x != (int) x) { // если x не целый
                                stack_push(st, NAN);
                                printf("Pow Error");
                                exit(0);
                            }
                        }
                        stack_push(st, pow(y, x));
                        break;
                    default:
                        break;
                }
                break;
            }
        }
        if (type_of_binary_operation == -1) { // тогда ищем унарную операцию
            for (int i = 0; i < 7; i++) {
                if (strcmp(elem, unar_operations[i]) == 0) {
                    type_of_unar_operation = i;
                    double x = stack_pop(st);
                    switch (type_of_unar_operation) {
                        case 0:
                            if (x < 0) {
                                stack_push(st, NAN);
                                printf("Pow Error");
                                exit(0);
                            }
                            stack_push(st, pow(x, 0.5));
                            break;
                        case 1:
                            stack_push(st, sin(x));
                            break;
                        case 2:
                            stack_push(st, cos(x));
                            break;
                        case 3:
                            if (2 * x / M_PI == (int) (2 * x / M_PI)) { // если при делении на пи/2 получилось целое число
                                stack_push(st, NAN);
                                printf("Tan Error");
                                exit(0);
                            }
                            stack_push(st, tan(x));
                            break;
                        case 4:
                            if (x <= 0) {
                                stack_push(st, NAN);
                                printf("LOG Error");
                                exit(0);
                            }
                            stack_push(st, log(x));
                            break;
                        case 5:
                            if (x <= 0) {
                                stack_push(st, NAN);
                                printf("LOG Error");
                                exit(0);
                            }
                            stack_push(st, log10(x));
                            break;
                        case 6:
                            stack_push(st, exp(x));
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }
        }
        if (type_of_unar_operation == -1 && type_of_binary_operation == -1) {
            printf("There is no such operation: \"%s\".", elem);
            stack_push(st, NAN);
            exit(0);
        }
    }
}

char **read_line(int *length) {
    char **words = (char **) calloc(1, sizeof(char *)); //исходный размер массива

    int i = 0;
    int j = 0;
    char c; //заготовка под чтение символов

    words[i] = (char *) calloc(1, sizeof(char)); //исходный размер слова

    printf("Enter the expression:\n");
    while ((c = getchar()) != '\n') //считываем посимвольно пока не наткнемся на конец строки
    {
        if (c != ' ') { //если это не пробел, то
            words[i] = (char *) realloc(words[i],
                                        (j + 1) * sizeof(char)); //увеличиваем размер текущего слова word[i] на j+1
            words[i][j] = c;//присваиваем текущему элементу слова значение считанного символа
            j++;//увеличиваем счетчик на 1
        } else {//иначе,
            words[i][j] = '\0';//присваиваем последнему элементу в слове символ конца слова
            j = 0;//обнуляем счетчик элементов в слове
            i++;//увеличиваем счетчик слов на 1
            words = (char **) realloc(words, (i + 1) * sizeof(char *)); //увеличиваем размер массива слов на 1
            words[i] = (char *) calloc(1, sizeof(char));
        }
    }
    words[i][j] = '\0';
    *length = i + 1;

    return words;
}

void calculate(const int length, char **expression) {
    struct Stack s;
    stack_init(&s);

    for (int elem = 0; elem < length; elem++) {
        add_to_stack(expression[elem], &s);
    }

    stack_print(&s);
}

void calculate_postfix_variable(const int length, char **expression, double x) {
    for (int i = 0; i < length; i++) {
        if (strcmp(expression[i], "x") == 0) {
            sprintf(expression[i], "%lf", x);
        }
    }
    calculate(length, expression);
}

int calculate_postfix(const int length, char **expression) {
    double x = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(expression[i], "x") == 0) {
            printf("Variable found. Enter its value.\n");
            scanf("%lf", &x);
            calculate_postfix_variable(length, expression, x);
            return 0;
        }
    }
    calculate(length, expression);
    return 0;
}

int main() {
    int length = 0;
    char **expression = read_line(&length);

    calculate_postfix(length, expression);

    return 0;

}