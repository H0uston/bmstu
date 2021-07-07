CC := gcc

CFLAGS := -std=c99 -Wall -Werror

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), drmemory)
	CFLAGS += -ggdb
endif

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

organize.o: organize.c organize.h function.h
	$(CC) $(CFLAGS) -c organize.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

main.o: main.c config.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c config.h
	$(CC) $(CFLAGS) -c test.c

test.exe: test.o io.o function.o
	$(CC) -o test.exe test.o io.o function.o

app.exe: main.o io.o organize.o function.o
	$(CC) -o app.exe main.o io.o organize.o function.o

make clean:
	$(RM) *.o *.exe