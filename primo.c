#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
int primo(int i){
    for(int j=3; j<=sqrt(i) +1 ; j+=2)
    {
        if(i % j==0)
        {
            return false;
        }
    }
    return true; 
}
int main(){

    int N = 1000000;
    int total = 0;
    double t1 = omp_get_wtime();

    #pragma omp parallel for schedule(guided) reduction (+:total) num_threads(4)
    for(int i =3; i<=N; i+=2)
    {
      if (primo(i))
      {
        total++;
      }else{}
    }
    total += 1;
    double t2 = omp_get_wtime();
    printf("Total de números primos entre 1 e %d: %d\n", N, total);
    printf("Tempo de execução: %f segundos\n", t2 - t1);


}
