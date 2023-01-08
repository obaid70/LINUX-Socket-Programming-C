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
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
    char message[100];
	char *hello = "Hello from client"; 
	struct sockaddr_in	 servaddr; 
    FILE * fptr = fopen("fileData.txt","r");
    fgets(message,100,fptr);
    int size=strlen(message);
    message[--size]='\0';
    printf("\nMESSAGE READ FROM FILE : %s\n",message);
    fclose(fptr);
    for(int i=0;i<strlen(message);i++)
    {
        if(message[i]>='a' && message[i]<='z')
        {
            message[i]+=3;
        }
        else if(message[i]>='A' && message[i]<='Z')
        {
            message[i]+=2;
        }
        else if(message[i]>='0' && message[i]<='9')
        {
            message[i]++;
        }
    }
    printf("\nEncrypted Message : %s\n",message);
	//Creating socket file descriptor 
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
	
	send(sockfd,message, strlen(message),0); 
	printf("\nEncrypted message sent to Server.\n"); 
		
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0'; 
	printf("\nDecrypted Message received from Server : %s\n", buffer); 
	
	
	close(sockfd); 
	return 0; 
} 

