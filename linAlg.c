/*
    Name: linAlg.c
    Purpose: Linear algebra functions used for numerical computations
*/

#include <stdio.h>
#include "linAlg.h"

void printMatrix(double **A, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf(STR_ENTRY, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int findMax(double *v, int n) {
    double max = v[0];
    int max_index = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
            max_index = i;
        }
    }
    return max_index;
}

int rowReduce(double **A, int m, int n) {
    // Find the pivot in each column
    int num_pivots = m < n ? m : n;
    int c = 0;  // Column
    for (int i = 0; i < num_pivots && c < n; i++ & c++) {
        // Get the column in v
        double v[m - i];
        for (int j = i; j < m; j++) {
            v[j - i] = A[j][c];
        }
        
        // Find the maximum value
        int max_index = findMax(v, m - i);
         
        if (v[max_index] < PRECISION &&
            v[max_index] > -PRECISION ) {
            i--;
            continue;
        }

        max_index += i;

        // Move that row to the top
        double *tmp;
        tmp = A[i];
        A[i] = A[max_index];
        A[max_index] = tmp;
        
        // Scale the row down
        for (int j = n - 1; j >=  i; j--) {
            A[i][j] /= A[i][c];
        }
        // And zero out the rest of the column
        for (int j = 0; j < m; j++) {
            if (j == i) {
                continue;
            }
            for (int k = n - 1; k >= 0; k--) {
                A[j][k] -= A[j][c] * A[i][k];    
            }
        }
    }
    return 0;
}


