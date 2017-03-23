#include <stdio.h>

void partialSum( int *A, int *B, int n);

int main ( void )
{
    int i;
    int X[4] = {1,3,-2,4};
    int Y[4];
    partialSum(X,Y, 4);
    for (i = 0; i < 4; i++)
    {
        printf("%d ",Y[i]);
    }
return 0;
}

void partialSum( int A[], int B[], int n)
{
    int partial = 0;
    int i;
    for (i=0; i < n; i++)
        {
            partial += A[i];
            B[i] = partial;

        }
}
