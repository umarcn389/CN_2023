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
	char buffer[MAXLINE];
	char hello[20] = "Hello";
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
	printf("\n Enter the message :");
        fgets(buffer,1024,stdin);

	sendto(sockfd,&buffer, strlen(buffer),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("\n Message sent.\n");
	memset(&buffer,0,sizeof(buffer));		
	recvfrom(sockfd,buffer, sizeof(buffer),
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	printf("\n From Server : %s",buffer);
	close(sockfd);
	return 0;
}
