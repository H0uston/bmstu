CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), drmemory)
	CFLAGS += -ggdb
endif

array_io.o: array_io.c array_io.h error.h config.h
	$(CC) $(CFLAGS) -c array_io.c

filter.o: filter.c filter.h error.h config.h
	$(CC) $(CFLAGS) -c filter.c

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c

main.o: main.c error.h array_io.h filter.h
	$(CC) $(CFLAGS) -c main.c 

app.exe: main.o array_io.o filter.o sort.o
	$(CC) -o app.exe main.o array_io.o filter.o sort.o

test.o: test.c filter.h sort.h config.h error.h array_io.h
	$(CC) $(CFLAGS) -c test.c
	
test.exe: test.o filter.o sort.o array_io.o 
	$(CC) -o test.exe test.o filter.o sort.o array_io.o

tick_sort.o: tick_sort.c sort.h
	$(CC) $(CFLAGS) -c tick_sort.c

tick_sort.exe: tick_sort.o sort.o
	$(CC) -o tick_sort.exe tick_sort.o sort.o
	
clean:
	$(RM) *.o *.exe *.gch