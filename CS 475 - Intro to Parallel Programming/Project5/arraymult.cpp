/***********************************************************
 *Project: Project 5 
 *Author: Jacob Leno
 *Date: 05/18/18
 **********************************************************/

#include <stdio.h>
#include "simd.p5.h"
#include <omp.h>

#define ARRAYSIZE 32000000
float arrayA[ARRAYSIZE], arrayB[ARRAYSIZE], arrayC[ARRAYSIZE];	

void arrayMult(float *arrA, float *arrB, float *arrC, int size);
float arrayMulRed(float *arrA, float *arrB, int size);

int main(int argc, char *argv[]){

	for(int i = 0; i < ARRAYSIZE; i++){
		arrayA[i] = 3;
		arrayB[i] = 5;
		arrayC[i] = 7;	
	}
		
	int testSizes[] = { 1000, 5000, 20000, 50000, 70000, 100000, 250000, 500000, 1000000, 2500000, 5000000, 10000000, 20000000, 32000000 };
	int size = sizeof(testSizes) / sizeof(testSizes[0]);
	float sum1, sum2;
	double nonsimdMultTime, simdMultTime, simdRedTime, nonsimdRedTime;
	double time0, time1;
	double maxMultSpeedup = 0, aveMultSpeedup = 0, maxRedSpeedup = 0, aveRedSpeedup = 0;

	printf("\n");
	for(int i = 0; i < size; i++){
		for(int j = 0; j < 5; j++){
			time0 = omp_get_wtime();
			SimdMul(arrayA, arrayB, arrayC, testSizes[i]); //Get SIMD mult time
			time1 = omp_get_wtime();
			simdMultTime = time1-time0;

			time0 = omp_get_wtime();
			arrayMult(arrayA, arrayB, arrayC, testSizes[i]); //Get nonSIMD mult time
			time1 = omp_get_wtime();
			nonsimdMultTime = time1-time0;

			time0 = omp_get_wtime();
			sum1 = SimdMulSum(arrayA, arrayB, testSizes[i]); //Get the SIMD reduction time
			time1 = omp_get_wtime();
			simdRedTime = time1-time0;

			time0 = omp_get_wtime();
			sum2 = arrayMulRed(arrayA, arrayB, testSizes[i]); //Get the nonSIMD reduction time
			time1 = omp_get_wtime();
			nonsimdRedTime = time1-time0;
			
			aveMultSpeedup += (nonsimdMultTime / simdMultTime);
			if((nonsimdMultTime / simdMultTime) > maxMultSpeedup) maxMultSpeedup = (nonsimdMultTime / simdMultTime);
			aveRedSpeedup += (nonsimdRedTime / simdRedTime);
			if((nonsimdRedTime / simdRedTime) > maxRedSpeedup) maxRedSpeedup = (nonsimdRedTime / simdRedTime);
		}
		aveMultSpeedup = aveMultSpeedup / 5.;
		aveRedSpeedup = aveRedSpeedup / 5.;
		printf("Array Size: %d\n", testSizes[i]);
		printf("Mult Speedup Average: %2.2lf\t Mult Speedup Max: %2.2lf\n", aveMultSpeedup, maxMultSpeedup);
		printf("Reduction Speedup Average: %2.2lf\t Reduction Speedup Max: %2.2lf\n\n", aveRedSpeedup, maxRedSpeedup);
		maxRedSpeedup = 0;
		maxMultSpeedup = 0;
		aveMultSpeedup = 0;
		aveRedSpeedup = 0;
	}

	return 0;
}

void arrayMult(float *arrA, float *arrB, float *arrC, int size){
	for(int i = 0; i < size; i++){
		arrC[i] = arrC[i] * arrB[i] * arrA[i];
	}
}

float arrayMulRed(float *arrA, float *arrB, int size){
	float sum;
	
	for(int i = 0; i < size; i++){
		sum += (arrA[i] * arrB[i]);
	}	
	return sum;
}
