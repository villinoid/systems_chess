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
int send, send_2, receive,receive_2;
int connection_made = 0;
int connection_broken = 1;
char room_name[256];//pipe name for second player

void handshake() {

    mkfifo("create_game", 0666); 
    printf("Opened Well Known Pipe\n");
    printf("Waiting For Handshake...\n");

    receive = open("create_game", O_RDONLY); 
    read(receive, input, buff_size); 
    printf("Received Information From Process %s\n", input);

    send = open(input, O_WRONLY);
    char server_pid[100];
    sprintf(server_pid, "%d", getpid());
    write(send, server_pid, buff_size);

    read(receive, room_name, buff_size);
    printf("%s\n", room_name);
	mkfifo(room_name, 0666);
	printf("Opened room\n");
	printf("Waiting For Handshake...\n");
	
	receive_2 = open(room_name, O_RDONLY);
    read(receive_2, input, buff_size);
	
    printf("Received Information From Process %s\n", input);

    send_2 = open(input, O_WRONLY);
    write(send_2, server_pid, buff_size);

    read(receive, room_name, buff_size);
    printf("%s\n", room_name);
	
    connection_made = 1;
    connection_broken = 1;
    remove("create_game");
}

char *count(char *string) {
    char *c = malloc(sizeof(char));
    c[0] = -1;
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
        connection_broken = 0;
        connection_made = 0;
    }
    if (signo == SIGINT) {
        remove("create_game");
        close(send);
        close(receive);
        exit(0);
    }
}

int main() {    
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    while(1) {
        if (connection_made) {
            if (connection_broken){
                read(receive, input, buff_size);
            }
            if (connection_broken){
                write(send_2, count(input), buff_size);
            }
        }
        else {
            handshake();
        }
    }
    
}
