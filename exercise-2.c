#include <stdio.h>
#include <stdlib.h>

void input(int *matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", matrix + i * col + j);
        }
    }
}

void findmax(int *matrix, int row, int col) {
    int maxSum = 0;
    int maxI = -1;
    int maxJ = -1;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int sum = 0;

            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if ((x != i || y != j) && x >= 0 && x < row && y >= 0 && y < col) {
                        sum += *(matrix + x * col + y);
                    }
                }
            }

            if (sum > maxSum || (sum == maxSum && (i < maxI || (i == maxI && j < maxJ)))) {
                maxSum = sum;
                maxI = i;
                maxJ = j;
            }
        }
    }

    printf("%d %d", maxI + 1, maxJ + 1);
}

int main() {
    int row, col;
    scanf("%d", &row);
    col = row;

    int *matrix = (int *)malloc(row * col * sizeof(int));

    input(matrix, row, col);
    findmax(matrix, row, col);

    free(matrix);

    return 0;
}
