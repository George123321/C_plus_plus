#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

#define inaccuracy 1e-8
#define BUFFER_SIZE 255
#define NUMBER_ELEMENTS 15
#define NUMBER_ONE_CHAR_ELEMS 7
#define NUMBER_OF_BINARY 5
#define NUMBER_OF_UNAR 7
#define NUMBER_OF_STACK_CONTAINS 13
typedef struct Stack STACK;

char one_char_elems[NUMBER_ELEMENTS][2] = {"+", "-", "*", "/", "^", "(", ")"};
char good_elems[NUMBER_ELEMENTS][6] = {"+", "-", "*", "/", "^", "(", ")", "sqrt", "sin", "cos", "tan", "ln", "log10",
                                       "exp", "x"};
char binary_operations[NUMBER_OF_BINARY][2] = {"+", "-", "*", "/", "^"};
char stack_contain[NUMBER_OF_STACK_CONTAINS][6] = {"(", "sqrt", "sin", "cos", "tan", "ln", "log10", "exp", "+", "-",
                                                   "*", "/", "^"};
int priority_stack[NUMBER_OF_STACK_CONTAINS] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4};
char unar_operations[NUMBER_OF_UNAR][6] = {"sqrt", "sin", "cos", "tan", "ln", "log10", "exp"};
char multi_char_elems[
        NUMBER_ELEMENTS - NUMBER_ONE_CHAR_ELEMS][6] = {"sqrt", "sin", "cos", "tan", "ln", "log10", "exp", "x"};
char str[BUFFER_SIZE];
int type_arr[BUFFER_SIZE];
char buffer[BUFFER_SIZE][BUFFER_SIZE];
char prefix[BUFFER_SIZE][BUFFER_SIZE];
int length = 0;

int is_good(char *elem) {
    for (int i = 0; i < NUMBER_ELEMENTS; i++) {
        if (strcmp(elem, good_elems[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_in_one_char_elems(char *elem) {
    for (int i = 0; i < NUMBER_ONE_CHAR_ELEMS; i++) {
        if (strcmp(elem, one_char_elems[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_in_multi_char_elems(char *elem) {
    for (int i = 0; i < NUMBER_ELEMENTS - NUMBER_ONE_CHAR_ELEMS; i++) {
        if (strcmp(elem, multi_char_elems[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_binary_operation(char *elem) {
    for (int i = 0; i < NUMBER_OF_BINARY; i++) {
        if (strcmp(elem, binary_operations[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_unar_operation(char *elem) {
    for (int i = 0; i < NUMBER_OF_UNAR; i++) {
        if (strcmp(elem, unar_operations[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void read_line_1() {
    char c;
    int i = 0;
    int j = 0;
    while ((c = getchar()) != '\n') {
        if (c != ' ') {
            buffer[i][j] = c;
            j++;
        } else {
            buffer[i][j] = '\0';
            j = 0;
            i++;
        }
    }
    length = i;
}

void read_line() {
    char c;
    str[0] = '(';
    int i = 1;
    while ((c = getchar()) != '\n') {
        str[i] = c;
        i++;
    }
    str[i] = ')';

    for (i = 0; i < strlen(str); i++) {
        char elem[] = {str[i], '\0'};
        if (str[i] == ' ') {
            type_arr[i] = 0;
        } else if (is_in_one_char_elems(elem)) {
            type_arr[i] = 1;
        } else {
            type_arr[i] = 2;
        }
    }

    int word_number = 0;
    for (i = 0; i < strlen(str); i++) {
        if (type_arr[i] == 1) {
            buffer[word_number][0] = str[i];
            buffer[word_number][1] = '\0';
            word_number++;
        } else if (type_arr[i] == 2) {
            int word_len = 0;
            while (type_arr[i + word_len] == 2) {
                buffer[word_number][word_len] = str[i + word_len];
                word_len++;
            }
            buffer[word_number][word_len] = '\0';
            word_number++;
            i = i + word_len - 1;
        }
    }
    length = word_number;
}

int word_is_number(char *word) {
    int number_of_points = 0;
    // проверим первый символ
    if (word[0] == '.') {
        number_of_points++;
    }
    if (!(isdigit(word[0]) | word[0] == '.')) {
        return 0;
    } else {
        if (strcmp(word, ".") == 0) { // на самом деле, костыль
            return 0;
        }
        for (int i = 1; i < strlen(word); i++) {
            if (!(isdigit(word[i]) | word[i] == '.')) {
                return 0;
            } else {
                if (word[i] == '.') {
                    number_of_points++;
                }
            }

        }
        if (number_of_points > 1) {
            return 0;
        } else {
            return 1;
        }
    }

}

int check_line() {
    for (int i = 0; i < length; i++) {
        if (!(word_is_number(buffer[i]) | is_good(buffer[i]))) {
            printf("Unknown expression: %s; program terminated\n", buffer[i]);
            exit(0);
        }
    }
    return 1;
}

int index_in_array(const char *elem) {
    int index = 0;
    while (index < NUMBER_OF_STACK_CONTAINS && strcmp(elem, stack_contain[index]) != 0) {
        index++;
    }
    if (index < NUMBER_OF_STACK_CONTAINS) {
        return index;
    } else {
        printf("There is no such elem\n");
        return -1;
    }
}

void to_prefix() {
    STACK opStack;
    stack_init(&opStack);
    int elem_number = 0;
    for (int i = 0; i < length; i++) {
        if (strcmp(buffer[i], "(") == 0) {
            stack_push(&opStack, buffer[i]);
        } else if (word_is_number(buffer[i]) | strcmp(buffer[i], "x") == 0) {
            strncpy(prefix[elem_number], buffer[i], strlen(buffer[i]));
            elem_number++;
        } else if (is_binary_operation(buffer[i])) {
            if (is_empty(&opStack)) {
                stack_push(&opStack, buffer[i]);
            } else if (priority_stack[index_in_array(opStack.head->s)] >
                       priority_stack[index_in_array(buffer[i])]) {
                while (!(is_empty(&opStack) | strcmp(opStack.head->s, "(") == 0)) {
                    strncpy(prefix[elem_number], stack_pop(&opStack), strlen(buffer[i]));
                    elem_number++;
                }
                stack_push(&opStack, buffer[i]);
            } else {
                stack_push(&opStack, buffer[i]);
            }
        } else if (is_unar_operation(buffer[i])) {
            stack_push(&opStack, buffer[i]);
        }
        if (strcmp(buffer[i], ")") == 0) {
            while (strcmp(opStack.head->s, "(") != 0) {
                char *to_stack = stack_pop(&opStack);
                strncpy(prefix[elem_number], to_stack, strlen(to_stack));
                elem_number++;
            }
            stack_pop(&opStack);
        }
    }

}

int main() {
    read_line();
    check_line();
    to_prefix();

    for (int i = 0; i < length; i++) {
        printf("%s ", prefix[i]);
    }


    return 0;
}