build: main.o data.o
	gcc -m32 -Wall -o demo_pretvori main.o pretvori.o

main.o: main.c pretvori.h
	gcc -m32 -Wall -c main.c

data.o: pretvori.c pretvori.h
	gcc -m32 -Wall -c pretvori.c

run: build
	./demo_pretvori 221A

clean:
	rm -f demo_pretvori