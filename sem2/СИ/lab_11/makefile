CC := gcc

CFLAGS := -std=c99 -Wall

ifeq ($(mode), memcheck)
	CFLAGS += -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3
endif


function.o: function.c function.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c function.h
	$(CC) $(CFLAGS) -c $<

test.exe: test.o function.o 
	$(CC) -o $@ $^

clean:
	$(RM) *.o *.exe *.gch
