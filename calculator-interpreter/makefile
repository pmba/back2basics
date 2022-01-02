all: main clean

main: main.o lexer.o token.o
	gcc -o main main.o libs/lexer.o libs/token.o

main.o: main.c
	gcc -o main.o main.c -c -W -Wall -pedantic

lexer.o: libs/lexer.c libs/lexer.h
	gcc -o libs/lexer.o libs/lexer.c -c -W -Wall -pedantic

token.o: libs/token.c libs/token.h
	gcc -o libs/token.o libs/token.c -c -W -Wall -pedantic

clean: 
	rm -rf */*.o *.o