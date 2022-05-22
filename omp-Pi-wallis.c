// author giannisjv
#include <stdio.h>
#include <omp.h>
#include <math.h>
//#define cores 4
int main(int *argc, char **argv){
    int N, i, c ,cores;
    double et, st,time[10], pi = 1.0;
    int begin = 100000000, end = 1000000000 ,step = 100000000;
    //printf("\n Give Number of loops: ");
	//scanf("%d",&N);
	
	printf("\nNumber of cores: ");
	scanf("%d",&cores);
	

   for(N=begin; N<=end; N+=step){
    
   for(c=1;c<=cores;c++){
    
    time[i] = 0;
	st = omp_get_wtime();
	
   
    	#pragma omp parallel for num_threads(c) reduction(*:pi)
        for (i=1; i<N; i++)
            pi *= (4.0 * i * i )/(4.0 * i * i - 1);
        pi *= 2;
     
    et = omp_get_wtime();
	time[i] = et - st;
	
        
        printf("\n %.10f\t",pi);
        printf("The time with %2d core is %10.6f\t\n",c,time[i]);

        pi = 1.0;
                }
    
    printf("\n The number of loops was 0 to %d\n",N);
    printf("\nPi %.10f", M_PI);
    }
    return 0;
    
} 

