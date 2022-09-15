#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SA struct sockaddr

int main(int argc, char **argv){
	
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	
	int sockfd;
	struct sockaddr_in server_addr, cli;
	char buffer[1024];
	socklen_t sz;
	
	//Socket creation
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&server_addr, '\0', sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	
	
	//Binding
	if ( ( bind(sockfd, (SA*)&server_addr, sizeof(server_addr)) ) < 0){
		perror("[-]bind error");
		exit(1);
	}
	
	//Recieve
	//Initialization
	bzero(buffer, 1024);
	sz = sizeof(cli);
	
	//Recieving data using recvfrom()
	recvfrom(sockfd, buffer, 1024, 0, (SA*)&cli, &sz);
	printf("Data recieved: %s\n", buffer);
	
	//Send
	//Initialization
	bzero(buffer, 1024);
	sz = sizeof(cli);
	
	//Recieving data using sendto()
	strcpy(buffer, "Hi from UDP server");
	sendto(sockfd, buffer, 1024, 0, (SA*)&cli, sizeof(cli));
	printf("Data send: %s\n", buffer);
	
	return 0;
}