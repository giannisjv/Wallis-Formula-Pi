/*
=========================================
|                                       |
| Hello Everyone this is my attempt to  |
| solve Wallis product in C with OpenMP |
| Run the program and see how Pi is     |
|                generated              |
|                                       |
| As you increase N, you increase the   |
| proximity of Pi, Try it for yourself  |
|                                       |
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
    
    double st_end, st_beg, st_CPU_time = 0; // Initiating the timers for static
    double dy_end, dy_beg, dy_CPU_time = 0; // Initiating the timers for dynamic
    double gui_end, gui_beg, gui_CPU_time = 0; // Initiating the timers for guided

    double sta_pi; // Pi variable for static
    double dyn_pi; // Pi variable for dynamic
    double gui_pi; // Pi variable for guided
printf("\n==================================== For N: %d The pi is ==================================================\n", N);
 printf("Pi Static\tTime Static\tPi Dynamic\tTime Dynamic\tPi Guided\tTime Guided\tChunk\tCores\n");
    for (chunk = 1; chunk <= 4096; chunk *= 2){ // Choosing chunk from 1 to 4096 with incremental rate
        for(c=1; c<=cores; c *= 2){ // Chosing the cores of your CPU incrementally 
            
	        st_beg = omp_get_wtime();
                sta_pi = static_Pi(chunk, c); // Using Static function for Pi wallis
            st_end = omp_get_wtime();

            dy_beg = omp_get_wtime();
                dyn_pi = dynamic_Pi(chunk, c); // Using Dynamic  function for Pi wallis
            dy_end = omp_get_wtime();

            gui_beg = omp_get_wtime();
                gui_pi = guided_Pi(chunk, c); // Using Guided function for Pi wallis
            gui_end = omp_get_wtime();
            
    
    st_CPU_time = st_end - st_beg; // Calculating time used for static
    dy_CPU_time = dy_end - dy_beg; // Calculating time used for Dynamic
    gui_CPU_time = gui_end - gui_beg; // Calculating time used for Guided
        
        printf("%5.10f\t%5.6f\t%5.10f\t%5.6f\t%5.10f\t%5.6f\t%2d\t%2d\n", sta_pi, st_CPU_time, dyn_pi, dy_CPU_time, gui_pi, gui_CPU_time, chunk, c);
    

        }
        printf("\n");
    }

    return 0;
    
} 


/*  To understand the fuctions below  read this.
    pragma uses
     
     - for (Indicates that it has to run a for. Collapse for manual determination of for.)
            (e.g #pragma omp parallel for collapse(2)
            for(.......){
                for(......)
                    // your code !!!
            })

     - shedule (Indicates the scheduler (""static or palallel or guided"", chunk))
                chunk indicates how the processes are shared amoung CPU cores.

     - num_threads (Indicates the number of cores will be used.)
                 (e.g. num_threads(4) in order to use (4) cores)

     - reduction (Indicates the operation on a variable)
                When a core finishes his processes, he will send 
                the sum of his operations to the master. Once every
                core will send all of his operations, the master will
                sum the result and save it to the variable in reduction.
                




 */

double static_Pi(int chunk, int core){ // Parallel function for Pi Wallis in Static 
double sum = 1.0;
	#pragma omp parallel for schedule(static, chunk) num_threads(core) reduction(*:sum)
        for (int i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}

double dynamic_Pi(int chunk, int core){ // Parallel function for Pi Wallis in Dynamic 
double sum = 1.0;
	#pragma omp parallel for schedule(dynamic, chunk) num_threads(core) reduction(*:sum)
        for (int i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}

double guided_Pi(int chunk, int core){ // Parallel function for Pi Wallis in Guided 
double sum = 1.0;
	#pragma omp parallel for schedule(guided, chunk) num_threads(core) reduction(*:sum)
        for (int i=1; i<=N; i++)
            sum *= (4.0 * i * i )/(4.0   * i * i - 1);
     return sum *= 2;
}