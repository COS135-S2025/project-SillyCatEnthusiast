serverAndClient: client server
	make client
	make server

# client make file
client: Cmain.o chat.o memory.o
	gcc   Cmain.o chat.o memory.o -o client -lncurses -lpthread

Cmain.o: Client/main.c Client/chat.h Client/memory.h
	gcc   Client/main.c -c -o Cmain.o

chat.o: Client/chat.c Client/chat.h
	gcc   Client/chat.c -c -o chat.o

memory.o: Client/memory.c Client/memory.h Client/chat.h
	gcc   Client/memory.c -c -o memory.o

# server make file
server: Smain.o connector.o linked.o
	gcc	Smain.o connector.o linked.o -o server -lncurses -lpthread

Smain.o: Server/main.c Server/connector.h Server/linked.h
	gcc	Server/main.c -c -o Smain.o

connector.o: Server/connector.c Server/connector.h Server/linked.h
	gcc	Server/connector.c -c -o connector.o

linked.o: Server/linked.c Server/linked.h
	gcc	Server/linked.c -c -o linked.o

clean: 
	rm -f server 
	rm -f client
	rm -f *.o
	