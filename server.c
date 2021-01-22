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
int send1, receive1;
int send2, receive2;
int connection_client_1 = 0;
int connection_client_2 = 0;

void handshake() {
	if(!connection_client_1) {
		mkfifo("1stPlayerPipe", 0666);
		printf("Opened Well Known Pipe\n");
		printf("Waiting For Handshake...\n");

		receive1 = open("1stPlayerPipe", O_RDONLY);
		read(receive1, input, buff_size);
		printf("Received Information From Process %s\n", input);

		send1 = open(input, O_WRONLY);
		char server_pid[100];
		sprintf(server_pid, "%d", getpid());
		write(send1, server_pid, buff_size);

		read(receive1, input, buff_size);
		printf("%s\n", input);
		connection_client_1 = 1;
		remove("1stPlayerPipe");
	}
	else{
		mkfifo("2ndPlayerPipe", 0666);
		printf("Opened Well Known Pipe\n");
		printf("Waiting For Handshake...\n");

		receive2 = open("2ndPlayerPipe", O_RDONLY);
		read(receive2, input, buff_size);
		printf("Received Information From Process %s\n", input);

		send2 = open(input, O_WRONLY);
		char server_pid[100];
		sprintf(server_pid, "%d", getpid());
		write(send2, server_pid, buff_size);

		read(receive2, input, buff_size);
		printf("%s\n", input);
		connection_client_2 = 1;
		remove("2ndPlayerPipe");
	}
}

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

static void sighandler(int signo) {
	if (signo == SIGPIPE) {
		printf("\n\nClient has disconnected...\n\n");
		connection_client_1 = 0;
	}
	if (signo == SIGINT) {//If ctrl+c close both CHECK
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
	signal(SIGPIPE, sighandler);


	while(1) {
		//Check client 1 connection
		printf("Checking Client 1:\n");
		if (!connection_client_1) {//If not connected hanshake
			handshake();
		}
		//Read from Client 1
        else{
		read(receive1, input, buff_size);
		printf("Server [Player 1] got: \"%s\"\n",input);
		write(send1, count(input), buff_size);
    }


		//Check client 2 connection
		printf("Checking Client 2:\n");
		if (!connection_client_2) {//If not connected hanshake
			handshake();
		}
		//Read from Client 2
        else{
		read(receive2, input, buff_size);
		printf("Server [Player 2] got: \"%s\"\n",input);
		write(send2, count(input), buff_size);
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
