#This is the Makefile

CFLAGS = -Wall -std=c99
LIB = -lm -g


all: oscillator_euler  oscillator_euler_symplectic oscillator_rk4

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^


oscillator_euler: euler.o oscillator.o
	$(CC) $(CFLAGS) -o oscillator_euler oscillator.c euler.c $(LIB)

oscillator_euler_symplectic: euler_symplectic.o oscillator.o
	$(CC) $(CFLAGS) -o oscillator_euler_symplectic oscillator.c euler_symplectic.c $(LIB)

oscillator_rk4: rk4.o oscillator.o
	$(CC) $(CFLAGS) -o oscillator_rk4 oscillator.c rk4.c $(LIB)

clean:
	rm -rf *o oscillator_euler oscillator_euler_symplectic oscillator_rk4