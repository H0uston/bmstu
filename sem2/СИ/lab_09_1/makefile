CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), drmemory)
	CFLAGS += -ggdb
endif

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

test.o: test.c function.h
	$(CC) $(CFLAGS) -c test.c

test.exe: test.o function.o
	$(CC) $(CFLAGS) -o test.exe test.o function.o

clean:
	$(RM) *.exe *.o *.gch