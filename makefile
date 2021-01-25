all: server.c chessboard.o client.o
	gcc  -o server server.c
	gcc  -o client client.o chessboard.o
client.o: client.c chessboard.h
	gcc  -c client.c
chessboard.o:
	gcc  -c chessboard.c
clean:
	rm *.o

