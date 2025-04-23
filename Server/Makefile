server: main.o
	gcc   main.o  -o server -lncurses

main.o: main.c
	gcc   main.c -c -o main.o

clean: 
	rm -f server
	rm -f *.o
	