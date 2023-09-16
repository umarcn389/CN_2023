// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 65535
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	int buffer[MAXLINE];
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	int n, len;
	float ans;	
	printf("\n Enter the no of elements : ");
        scanf("%d",&n);
	sendto(sockfd, &n, sizeof(int),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
        memset(&buffer,0,n*sizeof(int));
        printf("\n Enter the elements :");
        for(int i=0;i<n;i++)
        {
           printf("\n Enter the [%d] element : ",i);
           scanf("%d",&buffer[i]);
        }
        
        sendto(sockfd,&buffer,n*sizeof(int),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));		
	n = recvfrom(sockfd,&ans, sizeof(float),
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	printf("\n Average : %f\n", ans);
	
	close(sockfd);
	return 0;
}
