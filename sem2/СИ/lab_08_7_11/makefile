CC := gcc 

CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), drmemory)
	CFLAGS += -ggdb
endif

io.o: io.c io.h error.h config.h
	$(CC) $(CFLAGS) -c io.c

organize.o: organize.c organize.h io.h config.h error.h
	$(CC) $(CFLAGS) -c organize.c

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

main.o: main.c io.h error.h config.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c function.h io.h
	$(CC) $(CFLAGS) -c test.c

test.exe: test.o function.o io.o
	$(CC) $(CFLAGS) -o test.exe test.o function.o io.o

app.exe: main.o io.o organize.o function.o
	$(CC) $(CFLAGS) -o app.exe main.o io.o organize.o function.o

clean:
	$(RM) *.o *.exe *.gch
