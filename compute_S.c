#include "utils.h"	//needed for printResult() and standard libraries
#include<time.h>

int main(int argc, char **argv){
	if(argc != 2){
		printf("Input argument k was missing!\n\n");
		return 1;
	}

	int k = atoi(argv[1]);
	uint64_t n = (uint64_t)1 << k;
	double start_time, end_time;
	double total_time;
	
	double *v = malloc(n*sizeof(double));
	
	start_time = clock();

	//Compute the elements of v
	for(uint64_t i = 1; i <= n; i++)
		v[i-1] = 1/(double)(i*i);

	//Compute the partial sum S_n
	double S_n = 0;
	for(int64_t i = n-1; i >= 0; i--)
		S_n += v[i];

	end_time = clock();
	total_time = (end_time-start_time)/(double)CLOCKS_PER_SEC;

	//Print the result
	printResult(k, S_n, n, total_time);
	
	return 0;
}

