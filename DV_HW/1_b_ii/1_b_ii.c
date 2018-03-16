#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_in(char*, char**, int);
void print_res(char **, int *, int);
void sort_two_arrays_alphabetically(char **, int *, int);
void sort_two_arrays_freq(char **, int *, int);
char *file_to_string(FILE *, char *, long);
void string_to_bool(char *, int *);
int count_words(int, int *, int *);
void string_to_array(char **, char *, int *, int);
void count_freq_words(int *, char **, char **, int, int);
void write_res_in_file(char **, int *, int);
void str_to_lower(char *);


int main() {
    /* читаем наш файл */
    FILE *my_text = fopen("C:\\Users\\George\\Desktop\\git_projects\\C_plus_plus\\DV_HW\\1_b_ii\\text.txt", "r");

    if (my_text) {
        int res_status = 0;
        printf("If you want to sort the words alphabetically, type 0, if by frequency, type 1.\n");
        scanf("%d", &res_status);
        if (res_status != 0 & res_status != 1) {
            printf("Invalid input");
            return 0;
        }
        char *f_string = 0;
        long length;
        f_string = file_to_string(my_text, f_string, length);
        /* закроем файл */
        fclose(my_text);
        /* в итоге имеем в f_string цельную строку
        * сделаем to_lower */
        str_to_lower(f_string);
        /* сделаем bool array (не буква из алфавта) */
        int bool_array[strlen(f_string)];
        string_to_bool(f_string, bool_array);
        /* слова с дефисом будем считать за два */
        int number_of_words = 0;
        int max_len = 0;
        max_len = count_words(strlen(f_string), bool_array, &number_of_words);
        /* создаем array для слов */
        char *words[number_of_words];
        /* пока нули, будем записывать слово в words */
        string_to_array(words, f_string, bool_array, max_len);
        /* теперь нужно создать массив из неповторяющихся слов */
        /* будем держать 2 массива: неповторяющихся слов и соответственно их количества */
        char *words_original[number_of_words];
        /* будем бежать по words и добавлять в words_original слово, если его нет */
        int number_of_original_word = 0;
        for (int i = 0; i < number_of_words; i++) {
            if (!(is_in(words[i], words_original, number_of_original_word))) {
                words_original[number_of_original_word] = (char*)calloc(strlen(words[i]), sizeof(char) + 1);
                for (int j = 0; j < strlen(words[i]); j++) {
                    words_original[number_of_original_word][j] = words[i][j];
                }
                number_of_original_word++;
            }
        }
        /* дозабьем массив words_original нулями */
        for (int i = number_of_original_word; i < number_of_words; i++) {
            words_original[i] = "0";
        }

        int freq_words[number_of_original_word];
        for (int i = 0; i < number_of_original_word; i++) {
            freq_words[i] = 0;
        }

        count_freq_words(freq_words, words, words_original, number_of_words, number_of_original_word);
        /* осталось отсортировать в алфавитном порядке, переставляя и числа тоже */
        if (res_status == 0) {
            sort_two_arrays_alphabetically(words_original, freq_words, number_of_original_word);
        }
        if (res_status == 1) {
            sort_two_arrays_freq(words_original, freq_words, number_of_original_word);
        }
        write_res_in_file(words_original, freq_words, number_of_original_word);
        print_res(words_original, freq_words, number_of_original_word);

        int res = 0;
        for (int i = 0; i < number_of_original_word; i++) {
            res += freq_words[i];
        }

        /* освободим память */
        free(f_string);
        for (int i = 0; i < number_of_words; i++) {
            free(words[i]);
            free(words_original[i]);
        }
        free(words);
        free(words_original);
    }
    return 0;
}

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

/* функция, которая красиво печатает результат работы */
void print_res(char **words_original, int *count, int n) {
    printf("\nPrinting result:\n");
    for (int i = 0; i < n; i++) {
        printf("%s : %d\n", words_original[i], count[i]);
    }
}

/* функция, которая сортирует по алфавиту массив слов, делая то же с массивом частот слов */
void sort_two_arrays_alphabetically(char **words, int *count, int number) {
    /* сортировка пузырьком */
    for (int i = 0; i < number - 1; i++)
        for (int j = i + 1; j < number; j++)
            if(strcmp(words[i], words[j]) > 0) {
                char *tmp = words[i];
                words[i] = words[j];
                words[j] = tmp;

                int tmp_i = count[i];
                count[i] = count[j];
                count[j] = tmp_i;
            }
}

void sort_two_arrays_freq(char **words, int *count, int number) {
    for (int i = 0; i < number - 1; i++) {
        for (int j = i + 1; j < number; j++) {
            if (count[j] > count[i]) { // пока строгое неравенство
                char *tmp = words[i];
                words[i] = words[j];
                words[j] = tmp;

                int tmp_i = count[i];
                count[i] = count[j];
                count[j] = tmp_i;
            }
            if(count[j] == count[i]) { // надо сортировать по алфавиту
                if(strcmp(words[i], words[j]) > 0) {
                    char *tmp = words[i];
                    words[i] = words[j];
                    words[j] = tmp;

                    int tmp_i = count[i];
                    count[i] = count[j];
                    count[j] = tmp_i;
                }
            }
        }
    }
}

/* функция, которая читает тектовый файл и преобразует его в строку */
char *file_to_string(FILE *my_text, char *f_string, long length) {
    fseek(my_text, 0, SEEK_END); // ставим указатель на конец файла
    length = ftell(my_text); // узнаем длину, функция возвращает положение указателя
    fseek(my_text, 0, SEEK_SET); // ставим указатель на начало
    f_string = calloc(length, sizeof(char) + 1); // создаем строку нужной длины
    if (f_string) {
        fread(f_string, 1, length, my_text); // записываем в строку наш файл
    }
    return f_string;
}

/* функция, которая возвращает массив "не буква" */
void string_to_bool(char *f_string, int *bool_array) {
    for (int i = 0; i < strlen(f_string); i++) {
        if ((f_string[i] >= 'a' && f_string[i] <= 'z')) {
            bool_array[i] = 0;
        }
        else {
            bool_array[i] = 1;
        }
    }
}

/* функция, которая считает количество слов по bool-массиву и находит длинну самого длинного слова*/
int count_words(int l, int *bool_array, int *number_of_words) {
    int max_len_word = 0;
    int len_of_current_word = 0;
    /* Будем бежать по всей строке. Данный цикл не учтет последнее слово, если строка оканчивается на букву.
     * Тогда если она оканчивается на букву, добавим к количеству слов один.
     * Также будем считать максимальную длину слова. */
    for (int i = 0; i < l; i++) {
        if (bool_array[i] == 0) {
            while (bool_array[i + len_of_current_word] == 0) {
                len_of_current_word++;
            }
            i += len_of_current_word; // i указывает на 1
           *number_of_words += 1;
            if (len_of_current_word > max_len_word) {
                max_len_word = len_of_current_word;
            }
            len_of_current_word = 0;
        }
    }
    return max_len_word;
}

/* функция, которая преобразует строку в массив слов с помощью bool-массива */
void string_to_array(char **words, char *f_string, int *bool_array, int max_len) {
    int number_of_current_word = -1;
    for(int i = 0; i < strlen(f_string); i++) {
        char word[max_len];
        int len_of_word = 0;
        if (bool_array[i] == 0) {
            while (bool_array[i + len_of_word] == 0) {
                word[len_of_word] = f_string[i + len_of_word];
                len_of_word++;
            }
            i = i + len_of_word; // указывает на 1
            number_of_current_word++;
            words[number_of_current_word] = (char*)calloc(len_of_word, sizeof(char)+1);
            //записываем слово в слова
            for (int j = 0; j < len_of_word; j++) {
                words[number_of_current_word][j] = word[j];
            }
        }
    }
}

/* функция, которая считает частоту слов в тексте */
void count_freq_words(int *freq_words, char **words, char **words_original, int number_of_words, int number_of_original_word) {
    for (int i = 0; i < number_of_words; i++) {
        // теперь ищем это слово в original
        for (int j = 0; j < number_of_original_word; j++) {
            if (strcmp(words[i], words_original[j]) == 0) {
                freq_words[j]++;
                break; // делаем break, т.к. дальше искать нет смысла
            }
        }
    }
}

/* функция, которая записывает результат в файл*/
void write_res_in_file(char **words_original, int *count, int n) {
    FILE *f = fopen("C:\\Users\\George\\Desktop\\git_projects\\C_plus_plus\\DV_HW\\1_b_ii\\res.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s : %d\n", words_original[i], count[i]);
    }
}

void str_to_lower(char *str) {
    int i = 0;
    while (str[i]) {
        str[i] = (char)tolower(str[i]);
        i++;
    }
}