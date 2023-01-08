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
	struct sockaddr_in	 servaddr; 
	char * choice=(char *) malloc (100*sizeof(char));
	char * temp="received.";
	strcpy(choice,"yes");
	char port[100];
	char address[100];
	char * file=(char *)malloc(100*sizeof(char));
	size_t size=100;
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
	printf("\n\nInformation from server : \n\n");
	n = recv(sockfd, (char *)address, 100, 0);
	address[n]='\0';
	printf("\nClient IP Address : %s\n\n",address);
	send(sockfd,(const char *)temp,strlen(temp),0);
	n = recv(sockfd, (char *)port, 100, 0);
	port[n]='\0';
	printf("\n\nClient Port Number : %s\n\n",port);
	send(sockfd,(const char *)temp,strlen(temp),0);
	while(strcmp(choice,"yes")==0)
	{
		n = recv(sockfd, (char *)file, 100, 0);
		file[n]='\0';
		printf("\n%s\n\n",file);
		getline(&file,&size,stdin);
		file[strlen(file)-1]='\0';
		send(sockfd, (const char *)file, strlen(file),0);
		n = recv(sockfd, (char *)file, 100, 0);
		file[n]='\0';
		if(strcmp(file,"Requested File Not Found!")!=0)
		{
			printf("\nYour File content has been saved in file.txt inside home folder.\n");
			FILE * fptr = fopen("home/file.txt","a");
			fprintf(fptr,"%s ( Port : %s )",file,port);
			fprintf(fptr,"%s","\n");
			fclose(fptr);
		}
		else
		{
			printf("\n%s\n",file);
		}
		send(sockfd,(const char *)temp,strlen(temp),0);
		n = recv(sockfd, (char *)file, 100, 0); 
		file[n] = '\0'; 
		printf("\n%s\n\n",file);
		getline(&choice,&size,stdin);
		choice[strlen(choice)-1]='\0';
		send(sockfd,(const char *)choice,strlen(choice),0);
	}
	printf("\n\nClient Terminated!\n\n"); 
	close(sockfd); 
	free(choice);
	free(file);
	return 0; 
} 
