CFLAGS=-W -Wall -g
PROGRAMS=lstrip lcase lcount suniqargs suniq

all: $(PROGRAMS)

lstrip: lstrip.o
	gcc -o lstrip $^

lcase: lcase.o
	gcc -o lcase $^

lcount: lcount.o
	gcc -o lcount $^

suniqargs: suniqargs.o
	gcc -o suniqargs $^

suniq: suniq.o
	gcc -o suniq $^

lstrip.o: lstrip.c

lcase.o: lcase.c

lcount.o: lcount.c

suniqargs.o: suniqargs.c

suniq.o: suniq.c

clean:
	rm -f $(PROGRAMS) *.o
