#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int i, j, x, y, rows1, cols1, rows2, cols2, val, sum = 0;
    rows1 = 1000;
    cols1 = 1500;
    rows2 = 1500;
    cols2 = 1000;
    int** matrix1 = (int**)malloc(rows1*sizeof(int*));
    for (i = 0; i < rows1; i++)
        matrix1[i] = (int*)malloc(cols1*sizeof(int));
    int** matrix2 = (int**)malloc(rows2*sizeof(int*));
    for (i = 0; i < rows2; i++)
        matrix2[i] = (int*)malloc(cols2*sizeof(int));
    int** result = (int**)malloc(rows1*sizeof(int*));
    for (i = 0; i < rows1; i++)
        result[i] = (int*)malloc(cols2*sizeof(int));

    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            val = rand()%101;
            matrix1[i][j] = val;
        }
    }

    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            val = rand()%101;
            matrix2[i][j] = val;
        }
    }

    printf("Computing...\n");
    clock_t start = clock();
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            for (x = 0; x < rows2; x++) {
                sum = sum + matrix1[i][x]*matrix2[x][j];
            }
            result[i][j] = sum;
            sum = 0;
        }
    }
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
