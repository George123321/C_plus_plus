#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include <string.h>

#define MAX_SIZE 255


int read_line(char **words) {
    int i = 0;
    int j = 0;
    char c; //заготовка под чтение символов

    words[i] = (char*)calloc(1, sizeof(char)); //исходный размер слова

    printf("Enter the expression:\n");
    while ((c = getchar()) != '\n') //считываем посимвольно пока не наткнемся на конец строки
    {
        if (c != ' '){ //если это не пробел, то
            words[i]=(char*)realloc(words[i],(j + 1)*sizeof(char)); //увеличиваем размер текущего слова word[i] на j+1
            words[i][j] = c;//присваиваем текущему элементу слова значение считанного символа
            j++;//увеличиваем счетчик на 1
        }
        else{//иначе,
            words[i][j] = '\0';//присваиваем последнему элементу в слове символ конца слова
            j = 0;//обнуляем счетчик элементов в слове
            i++;//увеличиваем счетчик слов на 1
            words = (char**)realloc(words,(i + 1)*sizeof(char*)); //увеличиваем размер массива слов на 1
            words[i] = (char*)calloc(1,sizeof(char));
        }
    }
    words[i][j] = '\0';
    return i;
}

void add_to_stack(const char s, struct Stack *st) {

}

int main() {
    char **expression = (char**)calloc(1, sizeof(char*)); //исходный размер массива
    int length = read_line(expression) + 1;
    // теперь в expression хранится массив из слов
    printf("%d\n", length);

    return 0;

}