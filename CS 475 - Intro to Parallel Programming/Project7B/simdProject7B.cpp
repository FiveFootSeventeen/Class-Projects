/********************************************************
 *Author: Jacob Leno
 *Date: 06/04/18
 *Program: Project 7B
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "simd.p7b.h"

#define SIZE   32768
float Array[2*SIZE];
float  Sums[1*SIZE];

int main(int argc, char *argv[]){
	#ifndef _OPENMP
		fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
		return 1;
	#endif	

	int     Size;
	FILE *  fp;
	int     i;

	fp = fopen( "signal.txt", "r" );
	if( fp == NULL )
	{
		fprintf( stderr, "Cannot open file 'signal.txt'\n" );
		exit( 1 );
	}
	fscanf( fp, "%d", &Size );
	Size = SIZE;
	for( i = 0; i < Size; i++ )
	{
		fscanf( fp, "%f", &Array[i] );
		Array[i+Size] = Array[i];		// duplicate the array
	}
	fclose( fp );
	double time0 = omp_get_wtime();
	for( int shift = 0; shift < Size; shift++ )
	{

		float sum = 0.;
		Sums[shift] = SimdMulSum(&Array[0], &Array[0+shift], Size);	
	}
	double time1 = omp_get_wtime();

	float valPerSec = Size / (time1 - time0);
	printf("Autocorrelation Sums per second: %2.2lf\n", valPerSec);
	//printf("Values of the sums: \n\n");
	
/*
	for( int i = 1; i <= 512; i++){
		printf("%2.2lf ", Sums[i]); //Print out the values of I from 1 - 512
	}

	printf("\n");
*/

}
