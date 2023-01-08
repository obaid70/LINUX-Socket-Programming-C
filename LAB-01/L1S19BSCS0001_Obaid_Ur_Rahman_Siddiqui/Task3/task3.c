#include<stdio.h>
int main()
{
    int x = 0x3412;
    char * address = (char *)&x;
    printf("\n");
    for(int i=0;i<sizeof(x);i++)
    {
        printf("%.2x ",address[i]);
    }
    printf("\n\nIt is Little-Endian Machine\n\n");
    return 0;
}