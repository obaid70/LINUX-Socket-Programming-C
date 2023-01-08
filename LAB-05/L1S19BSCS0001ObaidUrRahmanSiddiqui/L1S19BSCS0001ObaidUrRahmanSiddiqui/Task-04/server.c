// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<pthread.h>
#define PORT	 8080 
#define MAXLINE 1024 
int client=0;
struct AllInfo{
char clientAddress[100];
int portNumber;
int newfd;
};

 void * ServerFunction(void * parameter)
 {
	int number=client;
    struct AllInfo * info = (struct AllInfo *) parameter;
	char temp[100];
    char filename[100];
    char choice[100]="yes";
	char * content=(char *) malloc (100*sizeof(char));
	size_t size=100;
	sprintf(content,"%d",info->portNumber);
	int n=0;
	send(info->newfd, (const char *)info->clientAddress, strlen(info->clientAddress),0); 
	n=recv(info->newfd, (char *)temp, 100,0);
	send(info->newfd, (const char *)content, strlen(content),0); 
	n=recv(info->newfd, (char *)temp, 100,0);
    while(strcmp(choice,"yes")==0)
    {
    	char *message = "Please Enter Data to Store in File."; 
        send(info->newfd, (const char *)message, strlen(message),0); 
		n = recv(info->newfd, (char *)filename, 100,0); 
		filename[n] = '\0'; 
		char portFile[100]="home/";
		int index=0;
		int i=5;
		for(i=5;i<strlen(content)+5;i++)
		{
			portFile[i]=content[index++];
		}
		portFile[i++]='.';
		portFile[i++]='t';
		portFile[i++]='x';
		portFile[i++]='t';
		portFile[i]='\0';
		FILE * fptr=fopen(portFile,"a");
		if(fptr!=NULL)
		{
			fprintf(fptr,"%s",filename);
			fprintf(fptr,"%s","\n");
			fclose(fptr);
			char *success="Data Written Successfully!";
			send(info->newfd, (const char *)success, strlen(success),0); 
		}
		else
		{
			char *error="Requested File Not Opened!";
			send(info->newfd, (const char *)error, strlen(error),0); 
		}
		n=recv(info->newfd, (char *)temp, 100,0);
		char *ask="Do you want to enter more data ? (yes/no)";
		send(info->newfd, (const char *)ask, strlen(ask),0); 
		n = recv(info->newfd, (char *)choice, 100,0);
		choice[n]='\0';
    }
	close(info->newfd);
	if(number!=1)
	{
		printf("\nClient %d has been served.\n\n",number-1);
	}
	else
	{
		printf("\nClient %d has been served.\n\n",number);
	}
	free(content);
	pthread_exit(NULL);		
}

// Driver code 
int main() { 
	int sockfd; 
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
	printf("\n\nServer Running ... \n\n");
	pthread_t T[5];
	struct AllInfo info[5];
	listen (sockfd,5);
	int newfd;
	while(1)
	{
        ++client;
		int len= sizeof(cliaddr), n; 
		newfd= accept(sockfd, (struct sockaddr*) &cliaddr, &len);
		strcpy(info[client-1].clientAddress,inet_ntoa(cliaddr.sin_addr));
        info[client-1].portNumber=cliaddr.sin_port;
        info[client-1].newfd=newfd;
		printf("\nServing Client %d ( IP Address : %s and Port : %d)\n\n",client,info[client-1].clientAddress,info[client-1].portNumber);
		pthread_create(&T[client-1],NULL,ServerFunction,(void*)&info[client-1]);
		if(client==5)
		{
			client=0;
		}
	}
	return 0; 
} 