#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

static const double S = 1.64493406684822643647241516664;

void printResult(int k, double S_n, uint64_t np, int skipHeader){
	if(!skipHeader)
		printf("%9s%25s%25s%9s\n", "k", "S_n", "|S-S_n|", "Storage");

	uint64_t storage = np*sizeof(S_n);
	if(storage <= 1000)
		printf("%9d%25.17f%25.17e%7dB\n", k, S_n, fabs(S_n - S), (int)storage);
	else if((storage /= 1000) <= 1000)
		printf("%9d%25.17f%25.17e%7dkB\n", k, S_n, fabs(S_n - S), (int)storage);
	else if((storage /= 1000) <= 1000)
		printf("%9d%25.17f%25.17e%7dMB\n", k, S_n, fabs(S_n - S), (int)storage);
	else
		printf("%9d%25.17f%25.17e%7dGB\n", k, S_n, fabs(S_n - S), (int)storage/1000);
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Input argument k_end was missing!\n\n");
		return 1;
	}

	//Initialize
	int k_start = 3, k_end = atoi(argv[1]);
	uint64_t n = 1 << k_start;

	for(int k = 3; k <= k_end; k++){
		//Allocate memory (this is valid C99)
		double *v = malloc(n*sizeof(double));

		//Compute the elements of v
		#pragma omp parallel for schedule(static)
		for(uint64_t i = 1; i <= n; i++){
			v[i-1] = 1/(double)(i*i);
		}

		//Compute the partial sum S_n
		double S_n = 0;
		#pragma omp parallel for reduction(+:S_n)
		for(size_t i = n; i > 0; i--)
			S_n += v[i-1];

		//Print the result
		printResult(k, S_n, n, k-3);	
		
		//Increment n
		n = n << 1;

		free(v);
	}

	return 0;
}

