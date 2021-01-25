all: server.c chessboard.o client.o
	gcc -g -o server server.c
	gcc  -g -o client client.o chessboard.o
client.o: client.c chessboard.h
	gcc  -g -c client.c
chessboard.o:
	gcc  -g -c chessboard.c
clean:
	rm *.o

