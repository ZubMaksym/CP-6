#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "function.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("This program solves SLAE using simple iteration method.\n");

    do {
        int n = 0;
        double epsilon = 0;
        const int max_iterations = 1000;
        int correctInput = 1;
        int choice = 0;
        int precision = 0;
        do {
            printf("Please, enter the number of rows and columns in system (n)x(n):\n");
            if (scanf("%d", &n) == 1 && n > 0) {
                fflush(stdin);
                correctInput = 0;
            } else {
                printf("Wrong Input! You should enter only positive numbers!\n");
                fflush(stdin);
            }
        } while (correctInput == 1);

        correctInput = 1;

        do {
            printf("Enter epsilon in range [1e-15; 1e-1]\n");
            if (scanf("%lf", &epsilon) == 1 && epsilon >= 1e-15 && epsilon <= 1e-1) {
                fflush(stdin);
                correctInput = 0;
                precision = (int)-log10(epsilon);
                //printf("Entered epsilon: %.*lf\n", precision, epsilon);
            } else {
                printf("Wrong Input! You should enter only NUMBERS in range [1e-15; 1e-1]!\n");
                fflush(stdin);
            }
        } while (correctInput == 1);

        double **A = (double **) malloc(n * sizeof(double *));
        if (A == NULL) {
            printf("Memory allocation error for matrix A.\n");
            return 0;
        }

        for (int i = 0; i < n; i++) {
            A[i] = (double *) malloc(n * sizeof(double));
            if (A[i] == NULL) {
                printf("Memory allocation error for row %d of matrix A.\n", i + 1);
                for (int j = 0; j < i; j++) {
                    free(A[j]);
                }
                free(A);
                return 0;
            }
        }

        double *b = (double *) malloc(n * sizeof(double));
        if (b == NULL) {
            printf("Memory allocation error for vector b.\n");
            for (int i = 0; i < n; i++) {
                free(A[i]);
            }
            free(A);
            return 0;
        }

        double *x = (double *) calloc(n, sizeof(double));
        if (x == NULL) {
            printf("Memory allocation error for x.\n");
            for (int i = 0; i < n; i++) {
                free(A[i]);
            }
            free(A);
            free(b);
            return 0;
        }

        double *x_new = (double *) malloc(n * sizeof(double));
        if (x_new == NULL) {
            printf("Memory allocation error for vector x_new.\n");

            for (int i = 0; i < n; i++) {
                free(A[i]);
            }
            free(A);
            free(b);
            free(x);
            return 0;
        }

        correctInput = 1;

        do {
            printf("Example of correct input:\n");
            printf("11  -3  5  =  14\n");
            printf("9   9  -5  =  21\n");
            printf("1   7  13  =  11\n\n");
            printf("Chose the way SLAE will be entered:\n");
            printf("1 - Enter manually\n(WARNING! If your diagonal elements will not be dominant(like in example), you may recive unexpected result)\n");
            printf("2 - Generate randomly\n");
            printf("Your choice:\n");
            if (scanf("%d", &choice) == 1 && (choice == 1 || choice == 2)) {
                fflush(stdin);
                correctInput = 0;
            } else {
                printf("Wrong input! Please, enter 1 or 2 to make a choice\n");
                fflush(stdin);
            }
        } while (correctInput == 1);

        switch (choice) {
            case 1: {
                manualInput(n, b, A);
                break;
            }
            case 2: {
                randomlyGenerated(n, b, A);
                break;
            }
        }

        int iterations = 0;
        while (iterations < max_iterations) {
            int converged = 1;
            for (int i = 0; i < n; i++) {
                x_new[i] = b[i];
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        x_new[i] -= A[i][j] * x[j];
                    }
                }
                x_new[i] /= A[i][i];

                if (fabs(x_new[i] - x[i]) > epsilon) {
                    converged = 0;
                }
            }
            iterations++;
            if (converged) {
                printf("System was solved after %d iterations.\n", iterations);
                break;
            }
            for (int i = 0; i < n; i++) {
                x[i] = x_new[i];
            }
        }
        printf("The solution of the system is:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %.*lf\n", i + 1, precision, x[i]);
        }

        if (iterations == max_iterations) {
            printf("Reached the maximum number of iterations (%d). The solution may not have fully converged.\n",
                   max_iterations);
        }

        for (int i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
        free(b);
        free(x);
        free(x_new);

        printf("\n\nWant to enter new SLAE? (y-yes) or press any other key to exit \n");

    }while ((getchar() == 'y' || getchar() == 'Y') && getchar() == '\n');

    return 0;
}