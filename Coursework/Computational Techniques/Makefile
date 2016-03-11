all: qr

C_FLAGS = -O3 -c -std=c99
FILES = main.o matrix.o

qr: $(FILES)
	gcc -O3 -Wall -o qr $(FILES) -lm

main.o: main.c
	gcc $(C_FLAGS) main.c

matrix.o: matrix.c
	gcc $(C_FLAGS) matrix.c

clean:
	rm -rf qr *.o

.PHONY: clean all
