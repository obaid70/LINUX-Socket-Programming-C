// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() 
{ 
	int sockfd; 
	char * buffer=(char*)malloc(MAXLINE*sizeof(char)); 
	char *hello = "Hello from client"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	connect (sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)); 
	int n, len; 
	size_t size=1024;
	while(1)
	{
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\nServer : %s\n", buffer); 
		getline(&buffer,&size,stdin);
		buffer[strlen(buffer)-1]='\0';
		send(sockfd, (const char *)buffer, strlen(buffer),0);
		if(strcmp(buffer,"EXIT")==0)
		{
			printf("\nClient Terminated.\n");
			break;
		}
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\n%s\n", buffer); 
		send(sockfd, (const char *)buffer, strlen(buffer),0);
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\n%s\n", buffer); 
		send(sockfd, (const char *)buffer, strlen(buffer),0);
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\n%s\n", buffer); 
		send(sockfd, (const char *)buffer, strlen(buffer),0);
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\n%s\n", buffer); 
		send(sockfd, (const char *)buffer, strlen(buffer),0);
		n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
		buffer[n] = '\0'; 
		printf("\n%s\n", buffer); 
		send(sockfd, (const char *)buffer, strlen(buffer),0);
	}	
	close(sockfd); 
	return 0; 
}