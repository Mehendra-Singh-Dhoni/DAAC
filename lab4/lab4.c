#include <stdio.h>
#include <stdbool.h>

#define N 8

int board[N][N];

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;
    return true;
}

bool solve(int col) {
    if (col >= N) {
        printBoard();
        return true;
    }
    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            res = solve(col + 1) || res;
            board[i][col] = 0;
        }
    }
    return res;
}

int main() {
    if (!solve(0))
        printf("No solution exists\n");
    return 0;
}
