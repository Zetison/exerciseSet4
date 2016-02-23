#include <omp.h> 	//needed for omp_get_wtime()
#include "utils.h"	//needed for printResult() and standard libraries

int main(int argc, char **argv){
	if(argc != 2){
		printf("Input argument k was missing!\n\n");
		return 1;
	}

	int k = atoi(argv[1]);
	uint64_t n = (uint64_t)1 << k;
	double start_time, end_time;
	double total_time;
	
	start_time = omp_get_wtime();
	double *v = malloc(n*sizeof(double));

	//Compute the elements of v
	#pragma omp parallel for schedule(static)
	for(uint64_t i = 1; i <= n; i++)
		v[i-1] = 1/(double)(i*i);

	//Compute the partial sum S_n
	double S_n = 0;
	#pragma omp parallel for reduction(+:S_n)
	for(int64_t i = n-1; i >= 0; i--)
		S_n += v[i];

	end_time = omp_get_wtime();
	total_time = end_time-start_time;

	//Print the result
	printResult(k, S_n, n, total_time);
	
	return 0;
}

