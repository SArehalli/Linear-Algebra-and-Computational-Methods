# Linear-Algebra-and-Computational-Methods

## What is this?

Personal experimentation with computational methods, ML techniques, and other fun applications of Linear Algebra

## Newton's Method

To compile and run:

```
make newton
./newton
```

In `newton.c`, you'll find the following lines:
```C
#define DIMENSION 3
...
// f: R3 -> R3
// This is the function you change if you want to calculate other things
void f(double *x, double *y) {
    y[0] = 3 * x[0] - 3;
    y[1] = x[1] * x[1] * x[1] + 1;
    y[2] = x[2] * x[2] - 2;
}
```

By default, `newton` will compute a root of this function, with the dimension specified by the define. Of course, if you change the dimension, be sure to modify the main function's printf and such to match.

## Perceptron

to compile and run,

```
make perceptron
./perceptron
```

The main function will calculate the weight vector, the coefficients w<sub>0</sub>...w<sub>n</sub> of the hyperplane w<sub>0</sub> + w<sub>1</sub>x<sub>1</sub> + ... w<sub>n</sub>x<sub>n</sub> = 0 separating the row vectors in `data.txt`, given that the vectors are linearly separable. 

`data.txt` is formatted as a csv, with the first entry of each row being the label (-1 or 1) and the rest being the 
entries of the training data. 

`perceptron.c` also contains a `perceptron_predict` method that can be used to classify other data using the weight vec

## Other Stuff

Stay tuned
