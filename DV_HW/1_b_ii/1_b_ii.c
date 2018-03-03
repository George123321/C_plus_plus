#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>

int main() {
    char *f_string = 0;
    int c;
    long length;
    FILE *my_text = fopen("C:\\Users\\George\\Desktop\\git_projects\\C_plus_plus\\DV_HW\\1_b_ii\\text.txt", "r"); // создание объекта файл, чтение
    /* распечатка текста
    if (my_text) {
        while ((c = getc(my_text)) != EOF) {
            putchar(c);
        }
        fclose(my_text); // закрывает файл
    }*/

    if (my_text) {
        fseek(my_text, 0, SEEK_END); // ставим указатель на конец файла
        length = ftell(my_text); // узнаем длину, функция возвращает положение указателя
        fseek(my_text, 0, SEEK_SET); // ставим указатель на начало
        f_string = calloc(length, sizeof(char) + 1); // создаем строку нужной длины
        if (f_string) {
            fread(f_string, 1, length, my_text); // записываем в строку наш файл
        }
        //f_string[length - 2] = '\0';
        fclose(my_text); // закрываем файл
        // в итоге имеем в f_string цельную строку
        /* сделаем to_lower */
        strlwr(f_string);
        /* сделаем bool array (in not буква из алфавта) */
        int bool_array[strlen(f_string)];
        for (int i = 0; i < strlen(f_string); i++) {
            if ((f_string[i] >= 'a' && f_string[i] <= 'z')) {
                bool_array[i] = 0;
            } else {
                bool_array[i] = 1;
            }
        }

        for (int i = 0; i < strlen(f_string); i++) {
            printf("%d", bool_array[i]);
        }
        int number_of_words = 0;
        /* будем предполагать, что строка начинается с буквы. к тому же слова с дефисом будем считать за два*/
        for (int i = 0; i < strlen(f_string); i++) {
            if (bool_array[i] == 1 && bool_array[i + 1] !=
                                      1) { // тут может быть выход за пределы, но строка в си заканчивается на \0, поэтому все должно быть норм
                number_of_words++;
            }
        }
        printf("\n%d", number_of_words);
        /* создаем array для слов */
        char *words[number_of_words];
        /* пока нули, будем записывать слово в words */
        /*
        int i = 0;
        int k = 0;
        for (int j = 0; j < number_of_words; j++) {
            while ((bool_array[i] == 0) && (i != strlen(f_string) + 1)) {
                words[j][k] = f_string[i];
                i++;
                k++;
            }
            k = 0;
            i++;
        }*/
        int number_of_current_word = -1;
        for(int i = 0; i < strlen(f_string); i++) {
            char word[30];
            int len_of_word = 0;
            if (bool_array[i] == 0) {
                while (bool_array[i + len_of_word] == 0) {
                    word[len_of_word] = f_string[i + len_of_word];
                    len_of_word++;
                }
                i = i + len_of_word; // указывает на 1
                number_of_current_word++;
                words[number_of_current_word] = (char*)calloc(len_of_word, sizeof(char)+1);
                /* записываем слово в слова */
                for (int j = 0; j < len_of_word; j++) {
                    words[number_of_current_word][j] = word[j];
                }
            }
        }
        printf("\n");
        for (int i = 0; i <= number_of_current_word; i++) {
            printf("%s ", words[i]);
        }

        printf("\n");
        printf(f_string);
    }
    return 0;
}

