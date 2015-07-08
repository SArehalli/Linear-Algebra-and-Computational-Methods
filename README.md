# Linear-Algebra-and-Computational-Methods

## What is this?

Personal experimentation with computational methods, ML techniques, and other fun applications of Linear Algebra

## Newton's Method

To compile:
```
make newton
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

## Other Stuff

Stay tuned
