CC := gcc
CFLAGS := -std=c99 -Wall -D TYPE=1
OBJS := test.o set_array.o

ifeq ($(type), list)
	CFLAGS := -std=c99 -Wall -D TYPE=2
	OBJS := test.o set_list.o
endif

ifeq ($(mode), valgrind)
	CFLAGS += -g0
endif

test.exe: $(OBJS)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.exe *.o