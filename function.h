#ifndef CP_6_FUNCTION_H
#define CP_6_FUNCTION_H
#endif //CP_6_FUNCTION_H
#include <time.h>
#include <stdio.h>
#include <math.h>

void manualInput(int n, double *b, double **A){
    printf("Enter the coefficients of matrix A (size %dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            if (scanf("%lf", &A[i][j]) == 1){
                fflush(stdin);
            } else{
                fflush(stdin);
            }
        }
    }
    printf("Enter the elements of vector b:\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d] = ", i + 1);
        if (scanf("%lf", &b[i]) == 1){
            fflush(stdin);
        } else{
            fflush(stdin);
        }
    }
}

void randomlyGenerated(int n, double *b, double **A) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
                row_sum += fabs(A[i][j]);
            }
        }
        A[i][i] = row_sum + ((double)rand() / RAND_MAX) * 10.0 + 1.0;
    }
    // Генерація вектора b
    for (int i = 0; i < n; i++) {
        b[i] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    }

    printf("Generated matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", A[i][j]); //epsilon
        }
        printf("\n");
    }

    printf("Generated vector b:\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d] = %lf\n", i + 1, b[i]); //epsilon
    }
}