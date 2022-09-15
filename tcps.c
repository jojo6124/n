#include<sys/socket.h>
#include<sys/types.h>//not needed in client program
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//Global constant variables
#define PORT 8080
#define MAX 80
#define SA struct sockaddr//Not needed in client

void func(int connfd){
	char buff[MAX];
	int n = 0;
	
	
	//Client Server Communication loop
	for(;;){
		//Read
		//Remove all values of buff
		bzero(buff, MAX);		
		
		//Reading client message using client socket descriptor i.e connfd
		read(connfd, buff, sizeof(buff));
		printf("From client: %s\nTo client:",buff);
		
		
		//Write
		
		n = 0;
		//We use while loop with getchar() to read sentences with spaces
		while( (buff[n++] = getchar()) != '\n');
		
		//Put buff in an if statement to exit if it ever writes 'exit'
		if(strcmpi("exit", buff , 4) == 0){
			printf("Server exiting...\n");
			break;
		}
		else
			write(sockfd, buff, sizeof(buff))
	}
	
}

int main(){
	
	//Socket descriptors are integer
	int sockfd,connfd,len;
	
	//server and client address
	struct sockaddr_in serv, cli;
	
	
	//Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);//Using SOCK_STREAM for TCP stream, AF_INET for communication with diffrent machines, No extra protocol
	
	//Assigning address of server to 'serv'
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);//'INADDR_ANY' allows server to recieve any client address
	serv.sin_port = htons(PORT);
	
	//Bind
	//Bind socket to port
	if((bind(sockfd, (SA*)&serv, sizeof(serv))) != 0){
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");
	
	//Listen
	//Listen for clients
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	
	
	//Accept
	//Store client info in 'cli' using accept
	connfd = accept(sockfd, (SA*)&cli, sizeof(cli));
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");
	
	//Call function server client communication
	func(connfd);
	
	//Close connection
	close(sockfd);
}