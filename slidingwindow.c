#include<stdio.h>

int main(){
	int numofframes,frames[20],window;
	printf("Enter no. of frames:");
	scanf("%d",&numofframes);
	
	printf("Enter frames:");
	for(int i = 0; i < numofframes; i++)
		scanf("%d",&frames[i]);
	
	printf("Enter window size:");
	scanf("%d", &window);
	
	printf("Assuming no corruption in data\n");
	for(int i = 0; i < numofframes; i++){
		if( (i+1) % window == 0){
			printf("%d\n",frames[i]);
			printf("Acknowlegement recieved by sender.\n");
		}
		else
			printf("%d\n",frames[i]);
	}
}
