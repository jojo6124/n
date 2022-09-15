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

int main(){
	int sockfd, len;
	char send[MAX], recv[MAX];
	
	
	//Socket Creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//Socket address creation
	struct sockaddr_in addr;
	
	//Initialize
	memset(&addr, '\0', sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	
	
	//Connect
	printf("Connecting...\n");
	connect(sockfd, (SA*)&addr, sizeof(addr));
	
	
	//Write
	printf("Enter file name:");
	scanf("%s", send);
	write(sockfd, send, MAX);
	
	
	//Reading file
	printf("Opening %s:\n", send);
	while((read(sockfd, recv, MAX)) != 0){
		printf("%s",recv);
	}
	
	
	//Close
	close(sockfd);
	
	return 0;
}