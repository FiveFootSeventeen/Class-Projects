/*********************************************************
 *Student: Jacob Leno
 *Assignment: Project 4
 *Date: 05/14/2018
 *Note: Agent added was PumaWithAGrainAllergy. Every 3 Pumas eat 1 deer per month
 * Every 3in of grain kills 1 puma per month. Pumas increase by 1 each month.
 *********************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>


int	NowYear;		// 2017 - 2022
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
int	NowNumPumas;

const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				50.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;

float SQR(float);
float Ranf(unsigned int *, float, float);
int Ranf(unsigned int *, int, int);
void GrainDeer();
void Grain();
void Watcher();
void PumaWithAGrainAllergy();

int main(int argc, char *argv[]){

	
	// starting date and time:
	NowMonth =    0;
	NowYear  = 2017;

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	NowHeight =  1.;
	NowNumPumas = 1;


	omp_set_num_threads( 4 );	// same as # of sections 
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		#pragma omp section
		{
			PumaWithAGrainAllergy( );	
		}
	}       // implied barrier -- all functions must return in order
		// to allow any of them to get past here
}

void GrainDeer(){
	while( NowYear < 2023 )
	{
		float deerSupported = NowHeight / ONE_DEER_EATS_PER_MONTH;
 		int tmpNumDeer = NowNumDeer;	
		int deerEaten = 0; 
		int tmpNumPumas = NowNumPumas;
		if (tmpNumPumas > 3) deerEaten = tmpNumPumas / 3; // Every three Pumas eat 1 deer each month

		tmpNumDeer = tmpNumDeer - deerEaten;
		if(tmpNumDeer < 0) tmpNumDeer = 0;

		if ((float)tmpNumDeer > deerSupported){
			tmpNumDeer -= 1;
		} else {
			tmpNumDeer += 1;
		}

		if (tmpNumDeer <  0) tmpNumDeer = 0;

		// DoneComputing barrier:
		#pragma omp barrier
		NowNumDeer = tmpNumDeer;
		// DoneAssigning barrier:
		#pragma omp barrier
		// DonePrinting barrier:
		#pragma omp barrier
	}
}


void Grain(){
	while( NowYear < 2023 )
	{
		float tmpNowHeight = NowHeight;
		float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
		float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
		
		tmpNowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		tmpNowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

		if (tmpNowHeight < 0) tmpNowHeight = 0;

		// DoneComputing barrier:
		#pragma omp barrier
		NowHeight = tmpNowHeight;
		// DoneAssigning barrier:
		#pragma omp barrier
		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void Watcher(){
	unsigned int seed = 0;
	while( NowYear < 2023 )
	{
		// DoneComputing barrier:
		#pragma omp barrier
		

		// DoneAssigning barrier:
		#pragma omp barrier

		printf("Current Year: %d Current Month: %d\n", NowYear, NowMonth);
		printf("Temp: %2.2lf\n", NowTemp);
		printf("Precip (in): %2.2lf\n", NowPrecip);
		printf("Grain Height (in): %2.2lf\n", NowHeight);
		printf("# Deer: %d\n", NowNumDeer);	
		printf("# Pumas: %d\n", NowNumPumas);
		printf("\n");

/*	Uncomment this code for data collection	
		printf("%2.2lf\n", ((5./9.)*(NowTemp-32)));
		printf("%2.2lf\n", (NowPrecip*2.54));
		printf("%2.2lf\n", (NowHeight*2.54));
		printf("%d\n", NowNumDeer);	
		printf("%d\n", NowNumPumas);
*/

		NowMonth += 1;

		if (NowMonth > 11){
			NowYear += 1;
			NowMonth = 0;
		}

		float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
		float temp = AVG_TEMP - AMP_TEMP * cos( ang );
		NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
		NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
		if( NowPrecip < 0. )
			NowPrecip = 0.;
		// DonePrinting barrier:
		seed++;
		#pragma omp barrier
	}
}

void PumaWithAGrainAllergy(){
	while( NowYear < 2023 )
	{
		
		int deerEaten = 0;
		int pumasDied = 0;
		int tmpNowNumDeer = NowNumDeer;
		int tmpNowNumPumas = NowNumPumas;
		int tmpHeight = NowHeight;
		if (tmpHeight > 3.) pumasDied = int(tmpHeight / 3.); //Every 3in of grain kills 1 puma per month
			
		tmpNowNumPumas++; //Pumas Increase by 1 each month

		tmpNowNumDeer = tmpNowNumDeer - deerEaten;	
		tmpNowNumPumas = tmpNowNumPumas - pumasDied;
		if(tmpNowNumPumas <= 0) tmpNowNumPumas = 0;

		// DoneComputing barrier:
		#pragma omp barrier
		NowNumPumas = tmpNowNumPumas;
		// DoneAssigning barrier:
		#pragma omp barrier

		// DonePrinting barrier:
		#pragma omp barrier
	}
}

float Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r(seedp);              // 0 - RAND_MAX
        return(low + r *(high - low) / (float)RAND_MAX);
}

int Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;
        return (int)(Ranf(seedp, low,high));
}


float SQR( float x )
{
        return x*x;
}
