#include<arpa/inet.h>//Not in client
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>//File
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define PORT 8080
#define MAX 60
#define SA struct sockaddr

char buff[MAX];

FILE *f1;
int main(){
	int sockfd, connfd, len;
	char send[MAX], recv[MAX];
	
	
	//Socket Creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//Socket address creation
	struct sockaddr_in serv,cli;
	
	//Initialize
	memset(&serv, '\0', sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(PORT);
	
	
	//Bind
	printf("Binding...\n");
	bind(sockfd, (SA*)&serv, sizeof(serv));
	
	
	//Listen
	printf("Listening...\n");
	listen(sockfd, 3);
	
	
	//Accept
	len = sizeof(cli);
	printf("Accepting");
	connfd = accept(sockfd, (SA*)&cli, &len);
	close(sockfd);
	
	//Read
	read(connfd, &recv, MAX);
	printf("File %s Sending...\n", recv);
	
	//Send file data
	f1 = fopen(recv, "r");
	
	//Infinite loop to send data
	while( ( fgets(buff, MAX, f1) ) != NULL){
		write(connfd, buff, MAX);
		printf("%s\n",buff);
	}
	
	
	//Close
	fclose(f1);
	printf("File Transferred\n");
	
	return 0;
}