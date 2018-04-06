#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include <string.h>
#include <ctype.h>

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

double calculate(const int length, const char **expression) {
    struct Stack s;
    stack_init(&s);

    for (int elem = 0; elem < length; elem++) {
        add_to_stack(expression[elem], &s);
    }

    //stack_print(&s);
    return stack_pop(&s);
}

double calculate_postfix_variable(const int length, const char **expression, double x) {
    char **expression_copy = (char **)malloc(length* sizeof(char *));
    for (int i = 0; i < length; i++) {
        expression_copy[i] = (char *)malloc(sizeof(expression[i]));
        strcpy(expression_copy[i], expression[i]);
    }

    for (int i = 0; i < length; i++) {
        if (strcmp(expression[i], "x") == 0) {
            sprintf(expression_copy[i], "%lf", x);
        }
    }
    return calculate(length, (const char**)expression_copy);;
}

double calculate_postfix(const int length, const char **expression) {
    double x = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(expression[i], "x") == 0) {
            printf("Variable found. Enter its value.\n");
            scanf("%lf", &x);
            return calculate_postfix_variable(length, expression, x);
        }
    }
    return calculate(length, expression);
}

double *linspace(double x_left, double x_right, int num) {
    double *x = malloc((num + 1) * sizeof(double));

    for (int i = 0; i <= num; i++) {
        x[i] = x_left + ((x_right - x_left) / num ) * i;
        //printf("%lf\n", x[i]);
    }
    return x;
}

double *func_array(const int length, const char **func, double *x, int num) {
    double *y = malloc((num + 1) * sizeof(double));

    for (int i = 0; i <= num; i++) {
        y[i] = calculate_postfix_variable(length, func, x[i]);
        //printf("%lf\n", y[i]);
    }
    return y;
}

void vec_x_y_file(double *x, double *y, int num) {
    FILE *f = fopen("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/1_c_ii/Output/data_x.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    } else {
        fprintf(f, "x,y\n");
        for (int i = 0; i <= num; i++) {
            fprintf(f, "%lf,%lf\n", x[i], y[i]);
        }
    }
}


int main() {
    int length = 0;
    const char **expression = (const char **)read_line(&length);

    int num = 1000;

    double *x = linspace(0, 100, num);
    double *y = func_array(length, expression, x, num);

    vec_x_y_file(x, y, num);

    return 0;

}