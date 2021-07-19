CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), memcheck)
	CFLAGS += -g
endif

my_string.o: my_string.c my_string.h config.h
	$(CC) $(CFLAGS) -c my_string.c

function.o: function.c function.h config.h error.h my_string.h
	$(CC) $(CFLAGS) -c function.c

main.o: main.c function.h config.h error.h my_string.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c function.h my_string.h
	$(CC) $(CFLAGS) -c test.c

test.exe: test.o function.o my_string.o
	$(CC) -o test.exe test.o function.o my_string.o

app.exe: main.o function.o my_string.o
	$(CC) -o app.exe main.o function.o my_string.o

clean:
	$(RM) *.exe *.o *.gch