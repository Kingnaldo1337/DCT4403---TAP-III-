#include <stdio.h>
#include <stdlib.h>
int main(){


int N = 10;
int count = 0;
int seed = 0;

srand(seed);

float x, y, d;

for (int i =0; i<N; i++)
{
    x = (float) rand() / RAND_MAX;
    y = (float) rand() / RAND_MAX;

    d = x * x + y * y;
    if (d<=1)
    {
        count++;
    }

    printf("x: %f, y: %f = d: %f\n", x, y, d);
}

printf ("PI: %f\n", 4.0*count/N);

return 0;
}