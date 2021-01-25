#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "chessboard.h"

int buff_size = 256;
int send, receive, server_pid;
int player_choice=0;

static void sighandler(int signo) {
	if (signo == SIGINT) {
		//experimented with a lot of ways, but sending a SIGPIPE signal to server most reliably reset it
		if (player_choice=='1'){
			kill(server_pid, SIGUSR1); //send the server information that client 1 disconnected
		}
		if (player_choice=='2'){
			kill(server_pid, SIGUSR2);//send the server information that client 2 disconnected
		}
		close(send);
		close(receive);
		exit(0);
	}
}

void fgets_format(char* s){
	int i=0;
	while(!(s[i]=='\n')) {
		i++;
	}
	s[i]=0;
}

int main() {
	signal(SIGINT, sighandler);
	char input[buff_size];
	char output[buff_size];
	int *move;
	char private_pipe[128];
	sprintf(private_pipe, "%d", getpid());
	mkfifo(private_pipe, 0666);

	char **chessboard=setup_board();

	//Query Player 1 or 2
	// /*
	printf("Do you want to be player 1 or 2: \n");
	player_choice=fgetc(stdin);
    printf("player_choice: %d\n", player_choice);
	if(player_choice=='1') {
		send = open("1stPlayerPipe", O_WRONLY);//Player 1
        printf("Sent1\n");
	}
	else{
		send = open("2ndPlayerPipe", O_WRONLY);//Player 2
        printf("Sent2\n");
	}
	// */
	//send = open("1stPlayerPipe", O_WRONLY);//Player 1
	write(send, private_pipe, buff_size);

	printf("Waiting For Response From Server\n");


	receive = open(private_pipe, O_RDONLY);
	read(receive, input, buff_size);
	remove(private_pipe);

	printf("Server PID: %d\n", atoi(input));
	server_pid = atoi(input);

	printf("Sending Message Back to Server to Complete Handshake \n");
	write(send, "Handshake Complete", buff_size);
	//program doesn't continue if i don't flush stdin for some reason?
	print_board(chessboard);


	while(1) {
		
		if (player_choice=='1'){//player 1 starts the game so it writes a move first
			printf("\nInput: \n");
			fgets(input, buff_size, stdin);
			fgets_format(input);
			move=move_parse(input);
			if (0){//REPLACE with move_valid when Yulin done
				while(0){//REPLACE with move_valid when Yulin done
					printf("Impossible move. Input another.\n");
					printf("\nInput: \n");
					fgets(input, buff_size, stdin);
					fgets_format(input);
					move=move_parse(input);
				}
			}
			
			chessboard[move[3]][move[4]]=chessboard[move[1]][move[2]];
			chessboard[move[1]][move[2]]=0;
			
			write_board(chessboard,input);

			write(send, input, buff_size);

			read(receive, output, buff_size);
			read_board(chessboard, output);
			printf("\nOutput:\n");
			print_board(chessboard);
		}
		else {
			read(receive, output, buff_size);
			read_board(chessboard, output);
			printf("\nOutput:\n");
			print_board(chessboard);
			
			printf("\nInput: \n");
			fgets(input, buff_size, stdin);
			fgets_format(input);
			move=move_parse(input);
			if (0){////REPLACE with move_valid when Yulin done
				while(0){////REPLACE with move_valid when Yulin done
					printf("Impossible move. Input another.\n");
					printf("\nInput: \n");
					fgets(input, buff_size, stdin);
					fgets_format(input);
					move=move_parse(input);
				}
			}
			
			chessboard[move[3]][move[4]]=chessboard[move[1]][move[2]];
			chessboard[move[1]][move[2]]=0;
			
			write_board(chessboard,input);

			write(send, input, buff_size);
		}
			
	}

	return 0;

}
