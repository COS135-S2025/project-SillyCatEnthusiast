server: main.o connector.o linked.o
	gcc	main.o connector.o linked.o -o server -lncurses -lpthread


main.o: main.c connector.h linked.h
	gcc	main.c -c -o main.o

connector.o: connector.c connector.h linked.h
	gcc	connector.c -c -o connector.o

linked.o: linked.c linked.h
	gcc	linked.c -c -o linked.o

clean: 
	rm -f server
	rm -f *.o
	