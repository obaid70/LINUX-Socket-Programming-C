#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

void * ThreadFunction(void * parameter)
{
    printf("\nName : Obaid-Ur-Rahman Siddiqui\n\n");
    printf("\nRegistration Number : L1S19BSCS0001\n\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t T1;
    pthread_create(&T1,NULL,ThreadFunction,NULL);
    pthread_join(T1,NULL);
    return 0;
}
