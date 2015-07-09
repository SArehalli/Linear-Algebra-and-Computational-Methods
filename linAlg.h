#ifndef LINALG_H

/* Constants */
#define PRECISION 0.0001
#define STR_ENTRY "%10.2f"

/* Prototypes */

int findMax(double*, int);

int deriv(void (*)(double*, double*), int, double*, double **);

void readMatrix(char*, double**, int, int);

void printMatrix(double**, int, int);

double** newMatrix(int, int);

void freeMatrix(double**, int);

double* newVector(int);

void freeVector(double*);

int rowReduce(double**, int, int);

double dot(double*, double*, int);

int sign(double);
#endif


