#include "linAlg.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Predict the label (-1 or 1) of x in R^n using weight vector w in R^(n+1)
// Note that w[0] is the bias.
int perceptron_predict(double *w, double *x, int n) {
    
    // Straight formula: w dot x + b
    return sign(dot(w + 1, x, n) + w[0]);
}


// Error function 
int error(double *w, double** data, int n, int k) {
    int sum = 0;
    for (int i = 0; i < k; i++) {
        int label = (int) data[i][0];
        sum += abs(perceptron_predict(w, data[i] + 1, n) - label); 
    }
    return sum;
}

/* Create the weight vector w
 *
 * w is an output parameter
 * data is the training data set
 * n is the dimension of the data
 * k is the number of training vectors
 * 
 * assume that v[0] for each vector is it's label
 */
void perceptron_train(double *w, double **data, int n, int k) {
    memset(w, 0, (n + 1) * sizeof(int));
    
    // Loop until it classifies the training set perfectly
    while (error(w, data, n, k) > 0) {

        // For each training vector
        for (int i =0; i < k; i++) {

            // If mislabeled
            if (data[i][0] * perceptron_predict(w, data[i] + 1, n) <= 0) {
                
                // update the bias 
                w[0] += data[i][0];

                // Update the weight vector
                for (int j = 1; j < n + 1; j++) {
                    w[j] += data[i][0] * data[i][j];
                }
            }
        }
    }
}

int main() {
    double w[5] = {0};
    double **data = newMatrix(5, 5);
   
    readMatrix("data.txt", data, 5, 5); 
    printMatrix(data, 5, 5);

    perceptron_train(w, data, 4, 5);
    printf("<%f, %f, %f, %f, %f>\n", w[0], w[1], w[2], w[3], w[4]);
}
