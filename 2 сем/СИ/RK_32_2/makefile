CC := gcc
CFLAGS := -std=c99 -Wall -g3

%.o: %.c
	$(CC) $(CFLAGS) -c $<

app.exe: main.o io.o process.o
	$(CC) -o $@ $^

test.exe: test.o io.o process.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o *.exe