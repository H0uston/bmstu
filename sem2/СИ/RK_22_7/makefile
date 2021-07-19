main.exe: main.o arr_io.o process.o
	gcc -o main.exe arr_io.o process.o main.o

arr_io.o: arr_io.c errors.h config.h
	gcc -std=c99 -Wall -Werror -pedantic -c arr_io.c

process.o: process.c config.h
	gcc -std=c99 -Wall -Werror -pedantic -c process.c 

main.o: main.c errors.h config.h
	gcc -std=c99 -Wall -Werror -pedantic -c main.c
	
test.exe: test.o process.o 
	gcc -o test.exe process.o test.o
	
test.o: test.c config.h
	gcc -std=c99 -Wall -Werror -pedantic -c test.c
	
clean:
	rm *.o *.exe