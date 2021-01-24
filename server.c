#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


int buff_size = 256;
char input[256];
int send1, receive1;//Send/Recieve pipe to player 1
int send2, receive2;//Send/Recieve pipe to player 2
int connection_client_1 = 0;//Is there a connection to player 1?
int connection_client_2 = 0;//Is there a connection to player 2?
int player_turn=1;//First turn is player 1's

void handshake() {
	//Player 1 Connection Process
	if(!connection_client_1) {
		//Well Known Pipe Setup
		mkfifo("1stPlayerPipe", 0666);
		printf("Opened Well Known Pipe\n");
		printf("Waiting For Handshake...\n");
		receive1 = open("1stPlayerPipe", O_RDONLY);
		//Player 1 send pid - name of its pipe - to server
		read(receive1, input, buff_size);
		printf("Received Information From Process %s\n", input);

		send1 = open(input, O_WRONLY);//Open player 1 pipe
		char server_pid[100];
		sprintf(server_pid, "%d", getpid());
		write(send1, server_pid, buff_size);//Write back to player 1

		read(receive1, input, buff_size);
		printf("[Player 1] %s\n", input);//Handshake complete message
		//read(receive1, input, buff_size);//read to eliminate "" - doesn't work if uncommented

		connection_client_1 = 1;//Set connection status to TRUE
		remove("1stPlayerPipe");//Remove Well Known Pipe
	}
	//Player 2 Connection Process
	else{
		//Well Known Pipe Setup
		mkfifo("2ndPlayerPipe", 0666);
		printf("Opened Well Known Pipe\n");
		printf("Waiting For Handshake...\n");
		receive2 = open("2ndPlayerPipe", O_RDONLY);
		//Player 1 send pid - name of its pipe - to server
		read(receive2, input, buff_size);
		printf("Received Information From Process %s\n", input);

		send2 = open(input, O_WRONLY);//Open player 2 pipe
		char server_pid[100];
		sprintf(server_pid, "%d", getpid());
		write(send2, server_pid, buff_size);//Write back to player 2

		read(receive2, input, buff_size);
		printf("[Player 2] %s\n", input);//Handshake complete message
		//read(receive2, input, buff_size);//read to eliminate "" - doesn't work if uncommented

		connection_client_2 = 1;//Set connection status to TRUE
		remove("2ndPlayerPipe");//Remove Well Known Pipe
	}
}

//Generic count characters function
char *count(char *string) {
	char *c = malloc(sizeof(char));
	int i;
	for (i = 0; i < strlen(string); i++) {
		if (string[i] != ' ') {
			(c[0])++;
		}
	}
	return c;
}

//Sighandler to cleanly exit
static void sighandler(int signo) {
	if (signo == SIGUSR1) {
		printf("\n\nClient 1 has disconnected...\n\n");
		connection_client_1 = 0;
	}
	if (signo == SIGUSR2) {
		printf("\n\nClient 2 has disconnected...\n\n");
		connection_client_2 = 0;
	}
	//CHECK IF THIS IS TRUE - If ctrl+c close both CHECK - DOESNT WORK????
	if (signo == SIGINT) {
		//Close both player's pipes
		remove("1stPlayerPipe");
		close(send1);
		close(receive1);
		remove("2stPlayerPipe");
		close(send2);
		close(receive2);
		exit(0);
	}
}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	int did_handshake=0;

	while(1) {
		did_handshake=0; //Was handshake done on cycle "bool" var
		//Check client 1 connection
		printf("Checking Client 1:\n");
		if (!connection_client_1) {//If not connected -> hanshake
			handshake();
			did_handshake=1;
		}
		//Check client 2 connection
		printf("Checking Client 2:\n");
		if (!connection_client_2) {//If not connected -> hanshake
			handshake();
			did_handshake=1;
		}
		sleep(1); //Debug Waiter

		//fflush(stdin); //Might be needed idk

		if(!did_handshake) {//Don't read right after handshake - causes probs?
			//Read from Client 1 send to Client 2
			if(player_turn==1) { //Yes its redundant but clearer
				printf("Waiting for move from [Player 1]\n");
				read(receive1, input, buff_size);
				printf("Server got [Player 1]: \"%s\"\n",input);
				write(send2, count(input), buff_size);
				player_turn=2;//Player 2's turn next
			}

			//Read from Client 2 send to Client 1
			else{
				printf("Waiting for move from [Player 2]\n");
				read(receive2, input, buff_size);
				printf("Server got [Player 2]: \"%s\"\n",input);
				write(send1, count(input), buff_size);
				player_turn=1;//Player 1's turn next

			}
		}
	}





	/*
	    while(1) {
	            //Check client 1
	    printf("Checking Client 1:\n");
	            if (connection_client_1) {
	                    read(receive1, input, buff_size);
	                    printf("Server [Player 1] got: \"%s\"\n",input);
	                    write(send1, count(input), buff_size);
	            }
	            else {
	                    handshake();
	            }
	            //Check client 2
	    printf("Checking Client 2:\n");
	            if (connection_client_2) {
	                    read(receive2, input, buff_size);
	                    printf("Server [Player 2] got: \"%s\"\n",input);
	                    write(send2, count(input), buff_size);
	            }
	            else {
	                    handshake();//Makes Player 2 Pipe

	            }

	    }
	 */

}
