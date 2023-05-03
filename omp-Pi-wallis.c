/*
=========================================
| Hello Everyone this is my attempt to  |
| solve Wallis product in C with OpenMP |
| Run the program and see how Pi is     |
|                generated              |
=========================================
*/

#include <stdio.h>
#include <omp.h>

#define N 100000000

double static_Pi(int chunk, int cores);
double dynamic_Pi(int chunk, int cores);
double guided_Pi(int chunk, int cores);

int main(int *argc, char **argv){
    
    int chunk; // chunk is a number that defines scheduler portion
    int i; // is used for a simple loop

    int  c, cores = omp_get_max_threads(); // how many cores  will be in use 
    // omp_get_max_threads() will get all of the cores of your CPU 
    
    double et, st, CPU_time = 0; // Initiating the timers
    double sta_pi; // Pi variable for static
    double dyn_pi; // Pi variable for dynamic
    double gui_pi; // Pi variable for guided

    for (chunk = 1; chunk <= 4096; chunk *= 2){
        for(c=1; c<=cores; c *= 2){
            
	        st = omp_get_wtime();
                sta_pi = static_Pi(chunk, c);

            et = omp_get_wtime();
    
    CPU_time = et - st;
        
        printf("\nThe pi is %5.10f\t", pi);
        printf("The time with %2d core and chunk %2d is %10.6f\t",c, chunk, CPU_time);

        }
        printf("\n");
    }

/*
    #pragma omp parallel for schedule(static, 4096) num_threads(c) reduction(*:pi)
        for (i=1; i<N; i++)
            pi *= (4.0 * i * i )/(4.0 * i * i - 1);
        pi *= 2;

    printf("\npi: %.6f\n", pi);
*/
    return 0;
    
} 

double static_Pi(int chunk, int core){
int i; 
double sum = 1;
	#pragma omp parallel for schedule(static, chunk) num_threads(core) reduction(*:sum)
        for (i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}

double dynamic_Pi(int chunk, int core){
int i; 
double sum = 1;
	#pragma omp parallel for schedule(static, chunk) num_threads(core) reduction(*:sum)
        for (i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}

double guided_Pi(int chunk, int core){
int i; 
double sum = 1;
	#pragma omp parallel for schedule(static, chunk) num_threads(core) reduction(*:sum)
        for (i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}