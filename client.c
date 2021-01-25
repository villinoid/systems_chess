#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <wchar.h>
#include <locale.h>
#include "chessboard.h"
#include "pieces.h"

int buff_size = 256;
int send, receive, server_pid;
int player_choice=0;
int both_connected=0;

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
	if (signo == SIGUSR1){
		both_connected=1;
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
	setlocale(LC_CTYPE, "");
	int c;
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	char input[buff_size];
	char output[buff_size];
	int *move;
	char private_pipe[128];
	sprintf(private_pipe, "%d", getpid());
	mkfifo(private_pipe, 0666);

	char **chessboard=setup_board();

	//Query Player 1 or 2
	// /*
	wprintf(L"Do you want to be player 1 or 2: \n");
	player_choice=fgetc(stdin);
    wprintf(L"player_choice: %d\n", player_choice);
	if(player_choice=='1') {
		send = open("1stPlayerPipe", O_WRONLY);//Player 1
        wprintf(L"Sent1\n");
	}
	else{
		send = open("2ndPlayerPipe", O_WRONLY);//Player 2
        wprintf(L"Sent2\n");
	}
	// */
	//send = open("1stPlayerPipe", O_WRONLY);//Player 1
	write(send, private_pipe, buff_size);

	wprintf(L"Waiting For Response From Server\n");


	receive = open(private_pipe, O_RDONLY);
	read(receive, input, buff_size);
	remove(private_pipe);

	wprintf(L"Server PID: %d\n", atoi(input));
	server_pid = atoi(input);

	wprintf(L"Sending Message Back to Server to Complete Handshake \n");
	write(send, input, buff_size);
	//program doesn't continue if i don't flush stdin for some reason?
	if (player_choice=='2'){
		print_board(chessboard);
	}
	else{
		print_flipped(chessboard);
	}


	while(1) {
		//while(!both_connected);
		
		if (player_choice=='1'){//player 1 starts the game so it writes a move first
			wprintf(L"\nInput: \n");
			fgets(input, buff_size, stdin);
			if (!(strcmp(input, "\n"))){
				fgets(input, buff_size, stdin);
				c=1;
			}
			fgets_format(input);
			move=move_parse(input);
			if (!move_valid(chessboard,move)){//REPLACE with move_valid when Yulin done
				while(!move_valid(chessboard,move)){//REPLACE with move_valid when Yulin done
					wprintf(L"Impossible move. Input another.\n");
					wprintf(L"\nInput: \n");
					fgets(input, buff_size, stdin);
					fgets_format(input);
					move=move_parse(input);
				}
			}
			wprintf(L"moves: %d, %d, %d, %d\n",move[0],move[1],move[2],move[3]);
			chessboard[move[2]][move[3]]=chessboard[move[0]][move[1]];
			chessboard[move[0]][move[1]]='+';
			print_flipped(chessboard);
			
			write_board(chessboard,input);
			wprintf(L"wrote: %s",input);
			write(send, input, buff_size);

			read(receive, output, buff_size);
			read_board(chessboard, output);
			wprintf(L"\nOutput:\n");
			print_flipped(chessboard);
		}
		else {
			read(receive, output, buff_size);
			read_board(chessboard, output);
			wprintf(L"\nOutput:\n");
			print_board(chessboard);
			
			wprintf(L"\nInput: \n");
			fgets(input, buff_size, stdin);
			if (!strcmp(input, "\n")){
				fgets(input, buff_size, stdin);
			}
			fgets_format(input);
			move=move_parse(input);
			if (!move_valid(chessboard,move)){////REPLACE with move_valid when Yulin done
				while(!move_valid(chessboard,move)){////REPLACE with move_valid when Yulin done
					wprintf(L"Impossible move. Input another.\n");
					wprintf(L"\nInput: \n");
					fgets(input, buff_size, stdin);
					fgets_format(input);
					move=move_parse(input);
				}
			}
			chessboard[move[2]][move[3]]=chessboard[move[0]][move[1]];
			chessboard[move[0]][move[1]]='+';
			print_board(chessboard);
			write_board(chessboard,input);

			write(send, input, buff_size);
		}
			
	}

	return 0;

}
