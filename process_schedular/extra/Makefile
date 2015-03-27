LIB=-lreadline 
CFLAGS=-DUNIX -ansi -pedantic-errors
DEBUG=-g
#DEBUG=

all: shell

shell:	server.c client.c 
	gcc $(CFLAGS) $(DEBUG) server.c client.c -o run $(LIB)
clean:
	rm -f shell *~

