all: assembler

assembler: ./out/assembler.o ./out/methods.o ./out/methods_tester.o
	gcc ./out/assembler.o ./out/methods.o ./out/methods_tester.o -o assembler

./out/assembler.o: assembler.c
	gcc -Wall -ansi -pedantic -c assembler.c -o ./out/assembler.o

# ./methods
./out/methods.o: ./methods/methods.c
	gcc -Wall -ansi -pedantic -c ./methods/methods.c -o ./out/methods.o

./out/methods_tester.o: ./methods/methods_tester.c
	gcc -Wall -ansi -pedantic -c ./methods/methods_tester.c -o ./out/methods_tester.o
