// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT 65535
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	int buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	int opt=1;
	//reuse open port
        if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
        {   
           perror("setsockopt");  
           exit(EXIT_FAILURE);  
        }  
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n,val,sum;
        float ans;
	
	len = sizeof(cliaddr); 
	printf("Message from Client : ");
	recvfrom(sockfd, &n, sizeof(int),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
        printf("\n Number of entries : %d",n);
        memset(buffer,0,sizeof(int)*n);
        recvfrom(sockfd, &buffer, n*sizeof(int),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
        sum = 0;
        printf("\n values are :");
  
        for(int i=0;i<n;i++)
         {
            printf(" %d" , buffer[i]);
            sum = sum + buffer[i];
         }
         ans = (float)sum/n;
         printf("\n Average : %f", ans);
	 sendto(sockfd,&ans,sizeof(float),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("\n Message sent.\n");
		
	return 0;
}
