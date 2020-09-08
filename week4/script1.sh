#!bin/bash
# compiles ex1.c and executes it 10 times
gcc -o ex1 ex1.c;
for var in {1..10}
do
	./ex1
done
