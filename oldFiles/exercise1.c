#include<stdio.h>
#include<stdlib.h>
#include<math.h>

static const double PI = 3.14159265358979323846;

int main(int argc, char **argv){
	if(argc != 2){
		printf("Input argument k_end was missing!\n\n");
		return 1;
	}
	//Initialize
	int k_start = 3, k_end = atoi(argv[1]);
	int n = (int)pow(2,k_start);

	printf("n\tS_n\t\t\t|S-S_n|\n");
	for(int k = k_start; k <= k_end; k++){
		//Allocate memory (this is valid C99)
		double v[n];

		//Compute the elements of v
		for(size_t i = 1; i <= n; i++)
			v[i-1] = 1/(double)(i*i);

		//Compute the partial sum S_n
		double S_n = 0;
		for(size_t i = 0; i < n; i++)
			S_n += v[i];

		//Print the result
		double S = PI*PI/6;
		printf("%d\t%.17g\t%.17g\n", n, S_n, fabs(S_n - S));
		
		//Increment n
		n = 2*n;
	}
	return 0;
}

