// Server side implementation of UDP client-server model 
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
	printf("\nServer is running ...\n");
	int sockfd; 
	fd_set readfds,writefds;
	struct timeval tv;
	char buffer[MAXLINE]; 
	char *hello = "Hi,\n\t Please enter any 2 numbers or type EXIT to exit."; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	FD_ZERO(&readfds);
	listen (sockfd,1);
	int newfd;
	FD_SET(sockfd,&readfds);
	tv.tv_sec=3600;
	tv.tv_usec=500000;
	int rv=select(sockfd+1,&readfds,&writefds,NULL,&tv);
	while(1)
	{
		if(rv==-1)
		{
			perror("select");
		}
		else if(rv==0)
		{
			perror("Timeout Occured.");
		}
		else
		{
			if(FD_ISSET(sockfd,&readfds))
			{
				int len= sizeof(cliaddr), n; 
				newfd= accept(sockfd, (struct sockaddr*) &cliaddr, &len);
				printf("\nServing new client.\n");
				while(1)
				{
					send(newfd, (const char *)hello, strlen(hello),0); 
					n = recv(newfd, (char *)buffer, MAXLINE,0); 
					buffer[n]='\0';
					if(strcmp(buffer,"EXIT")==0)
					{
						printf("Client is served.\n");
						close(newfd);
						break;
					}
					else
					{
						char * message=(char*)malloc(1024*sizeof(char));
						const char del[2]=",";
						char * token;
						token=strtok(buffer,del);
						int num1=atoi(token);
						token=strtok(NULL,del);
						int num2=atoi(token);
						sprintf(message,"Numbers : %d , %d",num1,num2);	
						send(newfd, (const char *)message, strlen(message),0);  
						n = recv(newfd, (char *)buffer, MAXLINE,0); 
						buffer[n]='\0';
						sprintf(message,"Sum : %d + %d = %d",num1,num2,num1+num2);	
						send(newfd, (const char *)message, strlen(message),0); 
						n = recv(newfd, (char *)buffer, MAXLINE,0); 
						buffer[n]='\0';
						sprintf(message,"Sub : %d - %d = %d",num1,num2,num1-num2);	
						send(newfd, (const char *)message, strlen(message),0);  
						n = recv(newfd, (char *)buffer, MAXLINE,0); 
						buffer[n]='\0';
						sprintf(message,"Div : %d / %d = %d",num1,num2,num1/num2);	
						send(newfd, (const char *)message, strlen(message),0);
						n = recv(newfd, (char *)buffer, MAXLINE,0); 
						buffer[n]='\0';
						sprintf(message,"Mul : %d * %d = %d",num1,num2,num1*num2);	
						send(newfd, (const char *)message, strlen(message),0);  
						n = recv(newfd, (char *)buffer, MAXLINE,0); 
						buffer[n]='\0';
					}
				}
			}
		}
	}
	close(sockfd);
	return 0; 
}