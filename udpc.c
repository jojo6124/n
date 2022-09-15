#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define SA struct sockaddr

int main(int argc, char **argv){
	if(argc != 2){
		printf("Argument incorrect...\n");
		exit(0);
	}
	
	
	//Intialize
	int port = atoi(argv[1]), sockfd;
	char *ip = "127.0.0.1", buffer[1024];
	socklen_t sz;
	
	//Socket
	//Socket creation
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//Initialize
	struct sockaddr_in addr;
	
	memset(&addr, '\0', sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	
	
	//Send data
	bzero(buffer, 1024);
	
	strcpy(buffer, "Hello from UDP client");
	
	sendto(sockfd, buffer, 1024, 0, (SA*)&addr, sizeof(addr));
	printf("Data send: %s\n", buffer);
	
	//Recieve data
	bzero(buffer, 1024);
	sz = sizeof(addr);
	
	recvfrom(sockfd, buffer, 1024, 0, (SA*)&addr, &sz);
	printf("Data recieved: %s\n", buffer);
	
	
	return 0;
}