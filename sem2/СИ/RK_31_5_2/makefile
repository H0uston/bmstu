CC := gcc

CFLAGS := -std=c99 -Wall -Werror 

function.o: function.c function.h config.h
	$(CC) $(CFLAGS) -c function.c

main.o: main.c config.h function.h
	$(CC) $(CFLAGS) -c main.c

app.exe: main.o function.o
	$(CC) -o app.exe main.o function.o
	
clean: 
	$(RM) *.o *.exe *.gch