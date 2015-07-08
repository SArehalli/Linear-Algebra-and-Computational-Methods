newton: newton.c linAlg.c
	gcc newton.c linAlg.c -o newton

clean: 
	rm *.o newton
