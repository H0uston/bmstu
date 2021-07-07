CC := gcc
CFLAGS := -std=c99 -Wall

ifeq ($(mode), memcheck)
	CFLAGS += -ggdb
endif

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< 

function.o: function.c function.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c config.h error.h
	$(CC) $(CFLAGS) -c $<

app.exe: main.o io.o function.o
	$(CC) -o $@ $^
	
clean:
	$(RM) *.o *.exe