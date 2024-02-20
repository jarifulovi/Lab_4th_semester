#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 10
int result[MAX_SIZE][MAX_SIZE];

void multiplyRow(int row, int col, int matrixA[MAX_SIZE][MAX_SIZE], int matrixB[MAX_SIZE][MAX_SIZE]) {
    for (int j = 0; j < col; j++) {
        result[row][j] = 0;
        for (int k = 0; k < col; k++) {
            result[row][j] += matrixA[row][k] * matrixB[k][j];
        }
    }
}

int main() {
    int row, col;

    printf("Enter the number of rows and columns for matrices: ");
    scanf("%d %d", &row, &col);

    int matrixA[MAX_SIZE][MAX_SIZE], matrixB[MAX_SIZE][MAX_SIZE];

    printf("Enter elements for Matrix A (%d x %d):\n", row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements for Matrix B (%d x %d):\n", col, row);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            scanf("%d", &matrixB[i][j]);
        }
    }

    int pid;
    for (int i = 0; i < row; i++) {
        pid = fork();
       
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) {
            // Child process multiplies a row
            multiplyRow(i, col, matrixA, matrixB);
        }
    }
    printf("Result Matrix:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
