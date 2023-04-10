#include <stdio.h>
#include <stdlib.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

int n = 1000;
int m = 1500;
int p = 1500;
int q = 1000;
int** mat1;
int** mat2;
int** res;

void* matrix_multiply(void* arg)
{
    int thread_id = *(int*)arg;
    int block_size = n / NUM_THREADS;
    int start = thread_id * block_size;
    int end = (thread_id == NUM_THREADS - 1) ? n : (thread_id + 1) * block_size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < q; j++) {
            int total = 0;
            for (int k = 0; k < p; k++) {
                total = total + mat1[i][k] * mat2[k][j];
            }
            res[i][j] = total;
        }
    }

    pthread_exit(NULL);
}

int main(void)
{
    mat1 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat1[i] = (int*)malloc(m * sizeof(int));
    mat2 = (int**)malloc(p * sizeof(int*));
    for (int i = 0; i < p; i++)
        mat2[i] = (int*)malloc(q * sizeof(int));
    res = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        res[i] = (int*)malloc(q * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int value = rand() % 101;
            mat1[i][j] = value;
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            int value = rand() % 101;
            mat2[i][j] = value;
        }
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    clock_t start = clock();
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
