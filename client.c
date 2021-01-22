#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int buff_size = 256;
int send, receive, server_pid;
int player_choice=0;

static void sighandler(int signo) {
	if (signo == SIGINT) {
		//experimented with a lot of ways, but sending a SIGPIPE signal to server most reliably reset it
		kill(server_pid, SIGPIPE);
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

	char private_pipe[128];
	sprintf(private_pipe, "%d", getpid());
	mkfifo(private_pipe, 0666);

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
	fflush(stdin);

	while(1) {
		printf("\nInput: \n");
		fgets(input, buff_size, stdin);
		fgets_format(input);

		write(send, input, buff_size);

		read(receive, output, buff_size);
		printf("\nOutput:\n");
		printf("Number of Characters: %d\n", output[0]);
	}

	return 0;

}
