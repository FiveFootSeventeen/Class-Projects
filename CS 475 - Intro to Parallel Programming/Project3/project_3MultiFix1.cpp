/*********************************
 * Author: Jacob Leno
 * Assignment: Project 3
 * Date: 04/30/18
 *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <assert.h>

struct s
{
         float value;
	 int pad[NUMPAD];
} Array[4];

int main(int argc, char **argv){
	 assert(argc > 1);
         omp_set_num_threads( NUMT );
 
         int someBigNumber = 100000000;
	 double time0 = omp_get_wtime(); 
         #pragma omp parallel for
         for( int i = 0; i < 4; i++ )
         {
                 for( int j = 0; j < someBigNumber; j++ )
                 {
                          Array[ i ].value = Array[ i ].value + 2.;
                 }
         }
	 double time1 = omp_get_wtime();

	 double dT = time1-time0; 
	 double speedup = atof(argv[1]) / dT;
	 printf("Speedup: %2.2lf\\n", speedup);
	 printf("Time: %2.8lf seconds", dT);
}
