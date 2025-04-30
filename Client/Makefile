chatter: main.o chat.o memory.o
	gcc   main.o chat.o memory.o -o chatter -lncurses

main.o: main.c chat.h memory.h
	gcc   main.c -c -o main.o

chat.o: chat.c chat.h
	gcc   chat.c -c -o chat.o

memory.o: memory.c memory.h chat.h
	gcc   memory.c -c -o memory.o

clean: 
	rm -f chatter
	rm -f *.o
	