#include <stdio.h>

void move(int *, const int *, int *, const int *, int, int, int[8][8]);
void reCount_accessibility(int[8][8], const int *, const int *, int[8][8]);

int main() {
    int board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

    int currentRow = 0;
    int currentColumn = 0;

    int count = 1;

    int accessibility[8][8];
    reCount_accessibility(accessibility, vertical, horizontal, board);

    currentRow = 7;
    currentColumn = 7;
    board[currentRow][currentColumn] = count;

    while (count < 64) {
        count++;
        int moveNumber = 0;
        int moveNumber_min = 0;
        int min_access = 10;
        for (moveNumber; moveNumber <= 7; moveNumber++) {
            /* будем бежать по всем способам и следить за: принадлежат ли итоговые значение currentCol и Row от 0 до 7,
             * за минимальностью показателя доступности, был ли сделан ход в эту клетку */
            if ((0 <= currentRow + vertical[moveNumber]) && (currentRow + vertical[moveNumber] <= 7) &&
                    (0 <= currentColumn + horizontal[moveNumber]) && (currentColumn + horizontal[moveNumber] <= 7) &&
                    (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] == 0)) {
                /* будем искать moveNumber с минимальным показателем доступности */
                if (accessibility[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] < min_access) {
                    min_access = accessibility[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]];
                    moveNumber_min = moveNumber;
                }
            }
        }
        /* проверим, что найденная клетка не занята */
        if (board[currentRow + vertical[moveNumber_min]][currentColumn + horizontal[moveNumber_min]] == 0) {
            move(&currentRow, vertical, &currentColumn, horizontal, moveNumber_min, count, board);
            reCount_accessibility(accessibility, vertical, horizontal, board);
        }
        else {
            printf("Algorithm has come to a standstill\n");
            return 0;
        }
    }

    printf("\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d | ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/* функция, которая делает сдвиг коня и записывает номер хода на доску */
void move(int *currentRow, const int vertical[8], int *currentColumn, const int horizontal[8], int moveNumber, int count, int board[8][8]) {
    *currentRow += vertical[moveNumber];
    *currentColumn += horizontal[moveNumber];
    board[*currentRow][*currentColumn] = count;
}

/* функция, которая пересчитывает таблицу дсступности */
void reCount_accessibility(int accessibility[8][8], const int vertical[8], const int horizontal[8], int board[8][8]) {
    for (int currentRow = 0; currentRow < 8; currentRow++) {
        for (int currentColumn = 0; currentColumn < 8; currentColumn++) {
            int moveNumber = 0;
            accessibility[currentRow][currentColumn] = 0;
            /* зануляем клетку. будем бежать по всем moveNumbers. Если верный индекс и
             * board[currentRow + vertical[moveNumber]][currentRow + horizontal[moveNumber]] == 0, прибавляем 1 */
            for (moveNumber; moveNumber <= 7; moveNumber++) {
                if ((0 <= currentRow + vertical[moveNumber]) && (currentRow + vertical[moveNumber] <= 7) &&
                    (0 <= currentColumn + horizontal[moveNumber]) && (currentColumn + horizontal[moveNumber] <= 7) &&
                    (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] == 0)) {
                    accessibility[currentRow][currentColumn]++;
                }
            }
        }
    }
}