CC := gcc
CFLAGS := -std=c99 -Wall -fpic

%.o: %.c
	$(CC) $(CFLAGS) -c $<

libfunc.so: function.o
	$(CC) -shared -o $@ $< -framework Python

clean:
	$(RM) *.so *.o *.exe