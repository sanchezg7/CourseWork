gcc -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -c main.c
gcc -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -c tests.c
gcc -c Fraction.c
gcc tests.o Fraction.o main.o -o main
