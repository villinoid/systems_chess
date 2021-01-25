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
		if (player_choice=='1') {
			kill(server_pid, SIGUSR1); //send the server information that client 1 disconnected
		}
		if (player_choice=='2') {
			kill(server_pid, SIGUSR2);//send the server information that client 2 disconnected
		}
		close(send);
		close(receive);
		exit(0);
	}
	if (signo == SIGUSR1) {
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

void save_game(char * save_name, char**board){
	int save_fd;
	//wprintf(L"----save_game func:\n");
	char input[buff_size];
	//char namesaved[]="save_game_TEST";
	save_fd=open(save_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	//wprintf(L"----save_game func OPENED:\n");
	///*
	//Save board state
	write_board(board, input);
	wprintf(L"Print Board before Save:%s\n",input);
	write(save_fd, input, buff_size);
	//*/
	close(save_fd);
	//wprintf(L"----save_game func CLOSED:\n");

}


int main() {
	setlocale(LC_CTYPE, "");
	int c;
	int need_to_read_save=1;
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	char input[buff_size];
	char output[buff_size];
	int *move;
	char private_pipe[128];
	char next_to_play_input;
	sprintf(private_pipe, "%d", getpid());
	mkfifo(private_pipe, 0666);

	char **chessboard=setup_board();

	//Query Player 1 or 2
	// /*
	wprintf(L"Do you want to be player 1 or 2: \n");
	player_choice=fgetc(stdin);
	//wprintf(L"player_choice: %c\n", player_choice);
	if(player_choice=='1') {
		send = open("1stPlayerPipe", O_WRONLY);//Player 1
		//wprintf(L"Sent1\n");
	}
	else{
		send = open("2ndPlayerPipe", O_WRONLY);//Player 2
		//wprintf(L"Sent2\n");
	}

	//SAVE GAME LOAD - Player 1
	if(player_choice=='1') {
		int load_game=0;
		wprintf(L"Do you want to load a saved game? (y/n) \n");
		load_game=fgetc(stdin);
		while(load_game!='y'&&load_game!='n') {
			load_game=fgetc(stdin);
		}
		//wprintf(L"Load game choice: %c\n", load_game);
		if(load_game=='y') {
			wprintf(L"Enter save name: \n");
			fgets(input, buff_size, stdin);
			//fgets(input, buff_size, stdin);
			while(input[0]=='\n') {
				fgets(input,buff_size, stdin);
			}
			fgets_format(input);


			wprintf(L"Loading Game - \"%s\"...\n",input);
			//ERNOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
			int saved_game_fd;
			saved_game_fd=open(input,O_RDONLY);
			read(saved_game_fd,input,buff_size);//Board state
			wprintf(L"Board: %s\n",input);

			//Assign read in values to Board
			read_board(chessboard,input);


		}
		else{
			wprintf(L"New Game...\n");
			//chessboard=setup_board(); - Already done
		}
	}

	//SAVE GAME LOAD




	// */
	//send = open("1stPlayerPipe", O_WRONLY);//Player 1
	write(send, private_pipe, buff_size);

	wprintf(L"Waiting For Response From Server...\n");


	receive = open(private_pipe, O_RDONLY);
	read(receive, input, buff_size);
	remove(private_pipe);

	wprintf(L"Server PID: %d\n", atoi(input));
	server_pid = atoi(input);

	wprintf(L"Sending Message Back to Server to Complete Handshake... \n");
	write(send, input, buff_size);

	//Deprecated after save game update
	/*
	   if (player_choice=='2') {
	        print_board(chessboard);
	   }
	   else{
	        print_flipped(chessboard);
	   }
	 */


	while(1) {
		while(!both_connected);

		if (player_choice=='1') {//player 1 starts the game so it writes a move first
			if(need_to_read_save) {
				//Send chessboard to player 2 (for saves)
				write_board(chessboard,input);
				write(send, input, buff_size);
				wprintf(L"\nBoard sent to Player 2 \n");
				wprintf(L"\nLoaded - Ready to Start:\n");
				print_flipped(chessboard);
				need_to_read_save=0;
			}
			//
			wprintf(L"\nInput: \n");
			fgets(input, buff_size, stdin);
			if (!(strcmp(input, "\n"))) {
				fgets(input, buff_size, stdin);
				c=1;
			}
			fgets_format(input);
			//SAVE GAME HERE
			if(!strcmp(input,"save")) {
				//wprintf(L"----Save got: %s\n",input);
				wprintf(L"Enter save name: \n");
				fgets(input, buff_size, stdin);
				fgets_format(input);
				save_game(input,chessboard);
				kill(server_pid, SIGUSR1);
				kill(getpid(),SIGINT);
			}
			//SAVE GAME HERE
			move=move_parse(input);
			if (!move_valid(chessboard,move,player_choice)) {
				while(!move_valid(chessboard,move,player_choice)) {
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
			//wprintf(L"wrote: %s\n",input);
			write(send, input, buff_size);

			read(receive, output, buff_size);
			//Check win
			//wprintf(L"\nChecking Win: %s\n",output);
			if(output[0]=='T'){
				wprintf(L"\nTHE GAME HAS ENDED!!! - BLACK WINS!!!\n");
				kill(getpid(),SIGINT);
			}
			if(output[0]=='t'){//This shouldnt actually do anything
				wprintf(L"\nTHE GAME HAS ENDED!!! - WHITE WINS!!!\n");
				kill(getpid(),SIGINT);
			}
			//wprintf(L"\nQue?\n");
			read_board(chessboard, output);
			wprintf(L"\nOutput:\n");
			print_flipped(chessboard);
		}
		else {
			//Read board state for saves
			if(need_to_read_save) {
				read(receive, output, buff_size);
				read_board(chessboard, output);
				wprintf(L"\nStart:\n");
				print_board(chessboard);
				need_to_read_save=0;
			}


			read(receive, output, buff_size);
			//Check win
			if(output[1]=='T')
				wprintf(L"\nTHE GAME HAS ENDED!!! - BLACK WINS!!!\n");
			if(output[1]=='t')
				wprintf(L"\nTHE GAME HAS ENDED!!! - WHITE WINS!!!\n");

			read_board(chessboard, output);
			wprintf(L"\nOutput:\n");
			print_board(chessboard);

			wprintf(L"\nInput: \n");
			fgets(input, buff_size, stdin);
			if (!strcmp(input, "\n")) {
				fgets(input, buff_size, stdin);
			}
			fgets_format(input);
			move=move_parse(input);
			if (!move_valid(chessboard,move,player_choice)) {////REPLACE with move_valid when Yulin done
				while(!move_valid(chessboard,move,player_choice)) {////REPLACE with move_valid when Yulin done
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
			//Check if king dead
			//wprintf(L"game_ended: %d\n",game_ended(chessboard));
			if(game_ended(chessboard)==1) {
				wprintf(L"\nTHE GAME HAS ENDED!!! - WHITE WINS!!!\n");
				write(send, "t", 1);
				kill(server_pid, SIGUSR1);
				kill(getpid(),SIGINT);
			}
			if(game_ended(chessboard)==2) {
				wprintf(L"\nTHE GAME HAS ENDED!!! - BLACK WINS!!!\n");
				write(send, "T", 1);
				kill(server_pid, SIGUSR1);
				kill(getpid(),SIGINT);
			}
			write_board(chessboard,input);

			write(send, input, buff_size);
		}

	}

	return 0;

}
