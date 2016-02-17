#include<stdio.h>	//needed for printf
#include<stdint.h>	//needed for uint64_t
#include<math.h>	//needed for fabs()
#include "utils.h"	//needed for printResult()

const double S = 1.6449340668482264364724151666; // S = pi^2/6

void printResult(int k, double S_n, uint64_t np, double elapsedTime){
	printf("%3s%21s%25s%14s%9s\n", "k", "S_n", "|S-S_n|", "Elapsed Time", "Storage");
	printf("%3d%21.17f%25.17e%14.6f", k, S_n, fabs(S_n - S), elapsedTime);
	uint64_t storage = np*sizeof(S_n);
	if(storage <= 1000)
		printf("%7dB\n", (int)storage);
	else if((storage /= 1000) <= 1000)
		printf("%7dkB\n", (int)storage);
	else if((storage /= 1000) <= 1000)
		printf("%7dMB\n", (int)storage);
	else
		printf("%7dGB\n", (int)storage/1000);
}

