CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

arr_input.o: arr_input.c arr_input.h config.h
	$(CC) $(CFLAGS) -c arr_input.c

arr_print.o: arr_print.c arr_print.h
	$(CC) $(CFLAGS) -c arr_print.c
	
process.o: process.c process.h
	$(CC) $(CFLAGS) -c process.c

main.o: main.c config.h arr_input.h arr_print.h process.h
	$(CC) $(CFLAGS) -c main.c

main.exe: arr_input.o arr_print.o main.o process.o 
	$(CC) -o main.exe arr_print.o arr_input.o main.o process.o
	
clean : 
	$(RM) *.o *.exe