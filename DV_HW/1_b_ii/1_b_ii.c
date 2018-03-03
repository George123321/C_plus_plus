#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>

int is_in(char*, char**, int);
int eq_str(char*, char*);

int main() {
    char *f_string = 0;
    int c;
    long length;
    FILE *my_text = fopen("C:\\Users\\George\\Desktop\\git_projects\\C_plus_plus\\DV_HW\\1_b_ii\\text.txt", "r"); // создание объекта файл, чтение

    if (my_text) {
        fseek(my_text, 0, SEEK_END); // ставим указатель на конец файла
        length = ftell(my_text); // узнаем длину, функция возвращает положение указателя
        fseek(my_text, 0, SEEK_SET); // ставим указатель на начало
        f_string = calloc(length, sizeof(char) + 1); // создаем строку нужной длины
        if (f_string) {
            fread(f_string, 1, length, my_text); // записываем в строку наш файл
        }
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
        /* теперь нужно создать массив из неповторяющихся слов */
        /* будем держать 2 массива: неповторяющихся слов и соответственно их количества */
        char *words_original[number_of_words];
        /* будем бежать по words и добавлять в words_original слово, если его нет */
        int number_of_original_word = 0;
        for (int i = 0; i < number_of_words; i++) {
            if (!(is_in(words[i], words_original, number_of_original_word))) {
                words_original[number_of_original_word] = (char*)calloc(strlen(words[i]), sizeof(char)+1);
                for (int j = 0; j < strlen(words[i]); j++) {
                    words_original[number_of_original_word][j] = words[i][j];
                }
                number_of_original_word++;
            }
        }
        words_original[number_of_original_word] = "\0"; // сделаем на всякий случай метку, что дальше идет бред

        int count_words[number_of_original_word];
        for (int i = 0; i < number_of_original_word; i++) {
            count_words[i] = 0;
        }

        for (int i = 0; i < number_of_words; i++) {
            /* теперь ищем это слово в original */
            for (int j = 0; j < number_of_original_word; j++) {
                if (eq_str(words[i], words_original[j])) {
                    count_words[j]++;
                    break;
                }
            }
        }
        /*
        int check = 0;
        for (int i = 0; i < number_of_original_word; i++) {check += count_words[i];}
        printf("%d ?= %d", number_of_words, check);
         */
        
    }
    return 0;
}

int eq_str(char* str1, char* str2) {
    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
}

int is_in(char* str, char** str_array, int number_of_elements) {
    if (number_of_elements == 0) {
        return 0;
    }
    int len_str = strlen(str);
    for (int i = 0; i < number_of_elements; i++) {
        for (int j = 0; j < len_str; j++) {
            if (str[j] == str_array[i][j]) {
                if(j == len_str - 1) {
                    return 1;
                }
            }
            else {
                break;
            }
        }
    }
    return 0;
}
