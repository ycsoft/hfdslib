#include <stdio.h>

void  print_prime(const int start, const int end)
{
    int i , j , k = 0;
    FILE *f = NULL;

    f = stdout;

    f = fopen("prime.txt","w+");

    fprintf(f,"************************Print Prime*****************************\n");
    for ( i = start; i <= end; ++i)
    {
        for ( j = 2; j < i; ++j)
        {
            if ( i % j == 0)
            {
                break;
            }
        }
        if( j == i)
        {
            k++;
            fprintf(f,"%d\t",i);
            if ( k % 10 == 0)
            {
                fprintf(f,"\n");
            }
        }
    }
    fprintf(f,"\n*****************Print Prime Over*************************\n");
    fclose(f);
}
