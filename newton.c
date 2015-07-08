
#include "linAlg.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define dx .01

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

// Newton's method 
void newton(void (*f)(double*, double*), int n, int iterations, double *a_n) {
    for (int i = 0; i < iterations; i++) {
        // Calculate the Jacobian [Df(a_n)]
        double **D = newMatrix(n, n + 1);
        (void) deriv(f, n, a_n, D);
       
        // Calculate f(a_n)
        double f_g[n];
        (*f)(a_n, f_g);

        // Calculate the solutions for [Df(a_n)]x = -f(a_n)
        for (int j = 0; j < n; j++) {
            D[j][n] = -f_g[j];
        }
        rowReduce(D, n, n + 1);

        // Calculate a_{n+1} = a_0 + x
        for (int j = 0; j < n; j++) {
            a_n[j] += D[j][n];
        }
        freeMatrix(D, n);
    }
}

// f: R3 -> R3
// This is the function you change if you want to calculate other things
void f(double *x, double *y) {
    y[0] = 3 * x[0] - 3;
    y[1] = x[1] * x[1] * x[1] + 1;
    y[2] = x[2] * x[2] - 2;
}

void main(void) {
    double a_n[3] = {3, 2, 1};
    newton(&f, 3, 100, a_n);
    printf("<%f, %f, %f>\n", a_n[0], a_n[1], a_n[2]);
}
