#include <stdio.h>

void move(int *currentRow, const int vertical[8], int *currentColumn, const int horizontal[8], int moveNumber, int count, int board[8][8]) {
    *currentRow += vertical[moveNumber];
    *currentColumn += horizontal[moveNumber];
    board[*currentRow][*currentColumn] = count;
}

void reCount_accessibility(int accessibility[8][8], const int vertical[8], const int horizontal[8], int board[8][8]) {
    for (int currentRow = 0; currentRow < 8; currentRow++) {
        for (int currentColumn = 0; currentColumn < 8; currentColumn++) {
            int moveNumber = 0;
            accessibility[currentRow][currentColumn] = 0;
            /* зануляем клетку. будем бежать по всем moveNumbers. Если верный индекс и
             * board[i + vertical[moveNumber]][j + horizontal[moveNumber]] == 0, прибавляем 1 */
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
    /* начнем с 3-4 */
    board[3][4] = count;
    currentRow = 3;
    currentColumn = 4;
    while (count < 64) {
        count++;
        int moveNumber = 0;
        int moveNumber_min = 0;
        int min_access = 10;
        for (moveNumber; moveNumber <= 7; moveNumber++) {
            /* будем бежать по всем и следить за: принадлежат ли итоговые значение currentCol и Row от 0 до 7,
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
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}