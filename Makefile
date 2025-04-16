
chat: main.o chat.o
	gcc -Wall -Wextra -g main.o chat.o -o chat

main.o: main.c chat.h
	gcc -Wall -Wextra -g main.c -c -o main.o

chat.o: chat.c chat.h
	gcc -Wall -Wextra -g main.c -c -o chat.o

clean: 
	rm -f chat
	rm -f *.o
	