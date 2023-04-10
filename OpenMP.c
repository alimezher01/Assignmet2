#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    int i, j, k, l, m, n, o, p, q = 0;
    double start_time, end_time;
    srand(time(NULL));
    m = 1000;
    n = 1500;
    o = 1500;
    p = 1000;
    int** matrix1 = (int**)malloc(m*sizeof(int*));
    for (i=0;i<m;i++)
        matrix1[i]=(int*)malloc(n*sizeof(int));
    int** matrix2=(int**)malloc(o*sizeof(int*));
    for (i=0;i<o;i++)
        matrix2[i]=(int*)malloc(p*sizeof(int));
    int** result=(int**)malloc(m*sizeof(int*));
    for (i=0;i<m;i++)
        result[i]=(int*)malloc(p*sizeof(int));

    for (i=0;i<m;i++) {
        for (j=0;j<n;j++) {
            k=rand()%101;
            matrix1[i][j]=k;
        }
    }

    for (i=0;i<o;i++) {
        for (j=0;j<p;j++) {
            k=rand()%101;
            matrix2[i][j]=k;   
        }
    }
    printf("Computing...\n");
    start_time=omp_get_wtime();
    omp_set_num_threads(4);
#pragma omp parallel for private(i,j,l,q)
    for (i=0;i<m;i++) {
        for (j=0;j<p;j++) {
            for (l=0;l<o;l++) {
                q = q + matrix1[i][l]*matrix2[l][j];
            }
            result[i][j] = q;
            q = 0;
        }
    }
    end_time=omp_get_wtime();
    printf("Time taken: %f seconds\n", end_time - start_time);
    return 0;
}
