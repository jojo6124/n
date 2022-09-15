#include<stdio.h>
#include<stdlib.h>

int main(){
	int i,j,noframes,x,x1=10,x2;
	
	for(i = 0;i < 10;i++)
		rand();
	
	noframes = rand() / 20000000;
	i = 1;
	j = 1;
	
	noframes = noframes / 8;
	printf("\nNo of frames is %d",noframes);
	while(noframes > 0){
	
		printf("\nSending frame %d", i);
		x = rand() % 10;
	
		if(x % 2 == 0){
			
			for(x2 = 1;x2 < 2;x2++){
				printf("\nWaiting for %d seconds\n",x2);
				sleep(x2);
			}
		
			printf("\nSending frame %d",i);
			x = rand() % 10;
		
		}
		
		printf("\nAck for frame %d",j);
		noframes -= 1;
		i++;
		j++;
	
	}
	printf("\nEnd of stop and wait protocol\n");
	return 0;
}