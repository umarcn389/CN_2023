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

int *sort(int *list,int n)
{
  int i,j,temp;
  for(i=0;i<n;i++)
   {
     for(j=0;j<n-1-i;j++)
      {
        if(*(list+j)>*(list+j+1))
         {
            temp = *(list+j);
            *(list+j) = *(list+j+1);
            *(list+j+1) = temp;
         }
      }
    }
   return list;
}
 	
// Driver code
int main() {
	int sockfd;
	int *buffer;
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
        buffer = (int*)calloc(n,sizeof(int));
        recvfrom(sockfd, buffer, n*sizeof(int),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
        printf("\n values are :");
        for(int i=0;i<n;i++)
           printf(" %d" , buffer[i]);
            
         buffer = sort(buffer,n);
         printf("\n Sorted List:" );
         for(int i=0;i<n;i++)
           printf(" %d" , buffer[i]);
	 sendto(sockfd,buffer,n*sizeof(int),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("\n Message sent.\n");
		
	return 0;
}
