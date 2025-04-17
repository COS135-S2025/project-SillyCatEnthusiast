
chatter: main.o chat.o
	gcc   main.o chat.o -o chatter

main.o: main.c chat.h
	gcc   main.c -c -o main.o

chat.o: chat.c chat.h
	gcc   chat.c -c -o chat.o

clean: 
	rm -f chatter
	rm -f *.o
	