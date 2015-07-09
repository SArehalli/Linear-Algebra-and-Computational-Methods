/*
    Name: linAlg.c
    Purpose: Linear algebra functions used for numerical computations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linAlg.h"

#define dx .1

// Calculate the Jacobian Matrix (matrix of partial derivatives 
int deriv(void (*f)(double*, double*), int n, double *x, double **J) {

    // For each variable
    for (int i = 0; i < n; i++) {
        double f_a0[n]; 
        (*f)(x, f_a0);
        
        double xdx[n];
        (void) memcpy(xdx, x, n * sizeof(double));
        xdx[i] += dx;
        
        double f_a1[n];
        (*f)(xdx, f_a1);

        // calculate the derivative with respect to that variable
        for (int j = 0; j < n; j++) {
            // And construct the jacobian
            J[j][i] = (f_a1[j] - f_a0[j])/dx;
        }
    }
    return n;
}

// Allocate a matrix on the heap
double** newMatrix(int m, int n) {
    double **D = malloc(m * sizeof(double *));
    for (int j = 0; j < m; j++) {
        D[j] = (double *) malloc(n * sizeof(double));
    }
    return D;
}

// Free the memory of a matrix on the heap
void freeMatrix(double **D, int m) {
    for (int i = 0; i < m; i++) {
        free(D[i]);
    }
    free(D);
}

double* newVector(int n) {
    return (double*) malloc(n * sizeof(double)); 
}

void freeVector(double *v) {
    (void) free(v);
}

void printMatrix(double **A, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf(STR_ENTRY, A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void readMatrix(char *filename, double **A, int m, int n) {
    FILE *fp = fopen(filename, "r");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%lf", &A[i][j]);
        }
    }
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

// Dot product 
double dot(double *v, double *w, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * w[i];
    }
    return sum;
}

// Returns the sign of a double
int sign(double x) {
    return x < 0.0? -1 : 1;  
}
