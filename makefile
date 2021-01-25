all: server.c chessboard.o client.o pieces.o
	gcc -g -o server server.c
	gcc -g -o client client.o chessboard.o pieces.o
client.o: client.c chessboard.h
	gcc -g -c client.c
chessboard.o:
	gcc -g -c chessboard.c pieces.h
pieces.o:
	gcc -g -c pieces.c
clean:
	rm *.o
