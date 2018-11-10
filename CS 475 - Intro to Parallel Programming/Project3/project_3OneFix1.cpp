/*********************************
 * Author: Jacob Leno
 * Assignment: Project 3
 * Date: 04/30/18
 *********************************/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

struct s
{
         float value;
	 int pad[NUMPAD];
} Array[4];

int main(){
         omp_set_num_threads(NUMT);
 
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
	
	 printf("%2.8lf", (time1-time0));
}
