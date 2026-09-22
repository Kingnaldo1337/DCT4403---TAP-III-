#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int main(){
unsigned long long int N= 1000000000; 
double integral = (exp(0) + exp(1)) / 2;
double h = (1.0 - 0)/N;
double t1 = omp_get_wtime();
#pragma omp parallel for reduction (+:integral)
for (unsigned long long int i = 1; i < N; i++)
{
    integral += exp(i * h);
}
double t2 = omp_get_wtime();
double integral_k = integral * h;
printf("Integral: %.20f\n", integral_k);
printf("Tempo de execução: %f segundos\n", t2 - t1);


}