newton: newton.c linAlg.c
	gcc newton.c linAlg.c -o newton

perceptron: perceptron.c linAlg.c
	gcc perceptron.c linAlg.c -o perceptron

clean: 
	-rm *.o 
	-rm newton
	-rm perceptron
