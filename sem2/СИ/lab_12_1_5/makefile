CC := gcc
CFLAGS := -std=c99 -Wall -Werror
OBJS := function.o

ifeq ($(mode), valgrind)
	CFLAGS += -g0
endif

ifeq ($(mode), drmemory)
	CFLAGS += -ggdb
endif

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(type), static_library)
	OBJS := libfunc.a
	CFLAGS += -D TYPE=1
endif

ifeq ($(type), dynamic_layout)
	OBJS := libfunc.so
	CFLAGS += -fPIC -D TYPE=2
endif

ifeq ($(type), dynamic_load)
	LOAD := libfunc.so
	OBJS :=
	CFLAGS += -fPIC -D TYPE=3
endif


%.o: %.c
	$(CC) $(CFLAGS) -c $<

libfunc.so: function.o
	$(CC) -shared -o $@ $<

libfunc.a: function.o
	ar rc $@ $<
	ranlib $@

app.exe: main.o $(OBJS) $(LOAD)
	$(CC) -o $@ main.o $(OBJS)

test.exe: test.o $(OBJS) $(LOAD)
	$(CC) -o $@ test.o $(OBJS)

clean:
	$(RM) *.o *.exe *.gch *.a *.so