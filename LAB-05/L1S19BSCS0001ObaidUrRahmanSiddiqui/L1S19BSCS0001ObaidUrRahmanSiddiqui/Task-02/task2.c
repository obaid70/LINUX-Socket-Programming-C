#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

struct Name_And_Reg
{
    char name[100];
    char Reg[100];
};

void * ThreadFunction( void * parameter)
{
    struct Name_And_Reg * info=(struct Name_And_Reg *)parameter;
    printf("\nName : %s\n\n",info->name);
    printf("\nRegistration Number : %s\n\n",info->Reg);
    pthread_exit(NULL);
}


int main()
{
    struct Name_And_Reg info;
    strcpy(info.name,"Obaid-Ur-Rahman Siddiqui");
    strcpy(info.Reg,"L1S19BSCS0001");
    pthread_t T1;
    pthread_create(&T1,NULL,ThreadFunction,(void*)&info);
    pthread_join(T1,NULL);
    return 0;
}