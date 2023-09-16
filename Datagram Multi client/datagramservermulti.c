// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	65535
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd,optval;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	//reuse address & port
        optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const void *)&optval , sizeof(int));	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n,flag;
	
       while(1)
        {
	      flag = 0;
              len = sizeof(cliaddr); //len is value/result
	      n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
	      buffer[n] = '\0';
              printf("Client : %s\n", buffer);
              if(strncmp(buffer,"EXIT",4) == 0 )
                     flag=1;
              sendto(sockfd,&buffer,sizeof(buffer),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	      printf("\n Message sent : %s",buffer);
              if(flag)
                break;
        }	
        close(sockfd);
	return 0;
}
