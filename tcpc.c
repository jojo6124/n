#include<netdb.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Global variables
#define PORT 8080
#define MAX 80
#define SA struct sockaddr

void func(int sockfd){
	char buff[MAX];
	int n = 0;
	
	
	//Client server communication loop
	for(;;){
		
		//Write 
		
		//Initalizing buffer
		bzero(buff, MAX);
		n = 0;
		
		//Reading string
		printf("Client: ");
		while( (buff[n++] = getchar()) != '\n');
		
		//Send message to server
		write(sockfd, buff,sizeof(buff));
		
		
		//Read
		//Initalizing buffer
		bzero(buff, MAX);
		
		//Retriving message from server 
		read(sockfd, buff, sizeof(buff));
		printf("Server: %s\n", buff);
		
		if((strncmp("exit", buff, 4)) == 0){
			printf("Exiting...\n");
			break;
		}
		
	}
	
}

int main(){
	int sockfd, connfd, len;
	
	
	//Socket Creation
	struct sockaddr_in cli;
	
	//Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	
	bzero(&cli, sizeof(cli));

	
	//Assign IP
	cli.sin_family = AF_INET;
	cli.sin_addr.s_addr = inet_addr("127.0.0.1");
	cli.sin_port = htons(PORT);
	
	//Connect
	//Connect to client
	
	len = sizeof(cli);
	if(connect(sockfd, (SA*)&cli, len) != 0){
		printf("Connection failed...\n");
		exit(0);
	}
	else 
		printf("Connnecting...\n");
	
	//Call function clier client communication
	func(sockfd);
	
	//Close connection
	close(sockfd);
	
	return 0;
}