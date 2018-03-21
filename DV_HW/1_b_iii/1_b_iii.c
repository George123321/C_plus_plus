#include <stdio.h>

#define BOARD_SIZE 8

void move(int *, const int *, int *, const int *, int, int, int[BOARD_SIZE][BOARD_SIZE]);

void reCount_accessibility(int[BOARD_SIZE][BOARD_SIZE], const int *, const int *, int[BOARD_SIZE][BOARD_SIZE]);

int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    /*
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }*/

    int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

    int currentRow = 0;
    int currentColumn = 0;

    int count = 1;

    int accessibility[BOARD_SIZE][BOARD_SIZE];
    reCount_accessibility(accessibility, vertical, horizontal, board);

    currentRow = 4;
    currentColumn = 3;
    board[currentRow][currentColumn] = count;

    while (count < BOARD_SIZE * BOARD_SIZE) {
        count++;
        int moveNumber = 0;
        int moveNumber_min = 0;
        int min_access = BOARD_SIZE * BOARD_SIZE;
        for (moveNumber; moveNumber <= 7; moveNumber++) {
            /* будем бежать по всем способам и следить за: принадлежат ли итоговые значение currentCol и Row от 0 до 7,
             * за минимальностью показателя доступности, был ли сделан ход в эту клетку */
            if ((0 <= currentRow + vertical[moveNumber]) && (currentRow + vertical[moveNumber] <= BOARD_SIZE - 1) &&
                (0 <= currentColumn + horizontal[moveNumber]) &&
                (currentColumn + horizontal[moveNumber] <= BOARD_SIZE - 1) &&
                (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] == 0)) {
                /* будем искать moveNumber с минимальным показателем доступности */
                if (accessibility[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] <
                    min_access) {
                    min_access = accessibility[currentRow + vertical[moveNumber]][currentColumn +
                                                                                  horizontal[moveNumber]];
                    moveNumber_min = moveNumber;
                }
            }
        }
        /* проверим, что найденная клетка не занята */
        if (board[currentRow + vertical[moveNumber_min]][currentColumn + horizontal[moveNumber_min]] == 0) {
            move(&currentRow, vertical, &currentColumn, horizontal, moveNumber_min, count, board);
            reCount_accessibility(accessibility, vertical, horizontal, board);
        } else {
            printf("Algorithm has come to a standstill\n");
            break;
            //return 0;
        }
    }

    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("  | ");
            } else {
                printf("%d | ", board[i][j]);
            }
        }
        printf("\n");
    }

    FILE *f = fopen("C:\\Users\\George\\Desktop\\git_projects\\C_plus_plus\\DV_HW\\1_b_iii\\res.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                fprintf(f, "  | ");
            } else {
                fprintf(f, "%d | ", board[i][j]);
            }
        }
        fprintf(f, "\n");
    }

    return 0;
}

/* функция, которая делает сдвиг коня и записывает номер хода на доску */
void move(int *currentRow, const int vertical[8], int *currentColumn, const int horizontal[8], int moveNumber, int count,
     int board[BOARD_SIZE][BOARD_SIZE]) {
    *currentRow += vertical[moveNumber];
    *currentColumn += horizontal[moveNumber];
    board[*currentRow][*currentColumn] = count;
}

/* функция, которая пересчитывает таблицу дсступности */
void reCount_accessibility(int accessibility[BOARD_SIZE][BOARD_SIZE], const int vertical[8], const int horizontal[8],
                           int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int currentRow = 0; currentRow < BOARD_SIZE; currentRow++) {
        for (int currentColumn = 0; currentColumn < BOARD_SIZE; currentColumn++) {
            int moveNumber = 0;
            accessibility[currentRow][currentColumn] = 0;
            /* зануляем клетку. будем бежать по всем moveNumbers. Если верный индекс и
             * board[currentRow + vertical[moveNumber]][currentRow + horizontal[moveNumber]] == 0, прибавляем 1 */
            for (moveNumber; moveNumber <= 7; moveNumber++) {
                if ((0 <= currentRow + vertical[moveNumber]) && (currentRow + vertical[moveNumber] <= BOARD_SIZE - 1) &&
                    (0 <= currentColumn + horizontal[moveNumber]) &&
                    (currentColumn + horizontal[moveNumber] <= BOARD_SIZE - 1) &&
                    (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] == 0)) {
                    accessibility[currentRow][currentColumn]++;
                }
            }
        }
    }
}