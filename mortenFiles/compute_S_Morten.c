#include<time.h>	//needed for clock(), ...
#include "utils.h"	//needed for printResult()
#include <math.h>

double calcSum(double *arr, int n, double ref, double *err) {
	double sum = 0.0;
	for (int64_t i = n-1; i >= 0; i--) {
		sum += arr[i];
	}

	*err = ref - sum;

	return sum;
	
}

double *createArray(uint64_t n) {
	double *v = (double*)malloc(n*sizeof(double));
	//Compute the elements of v
	for(uint64_t i = 1; i <= n; i++)
		v[i-1] = 1/(double)(i*i);

	return v;
                                        
}

void getSizeString(uint64_t size, char *str) {
	if (size < (1<<10)) {
		sprintf(str,"%dB", (int)size);
	} else if (size < (1 << 20)) {
		sprintf(str,"%dkiB", (int)(size >> 10));
	} else if (size < (1 << 30)) {
		sprintf(str,"%dMiB", (int)(size >> 20));
	} else {
		sprintf(str,"%dGiB", (int)(size >> 30));
	}

}


int main(int argc, char **argv){
	if(argc != 2){
		FILE *fp = fopen("timings_serial.txt", "w");
		for (int k = 0; k <= 30; k++) {
			int n_avg = 10;
			double init_time_avg = 0.0;
			double sum_time_avg = 0.0;
			double err_avg = 0.0;
			double err_avg2 = 0.0;
			
			uint64_t n = (uint64_t)1 << k;
			double sum;
			for (int j = 0; j < n_avg; j++) {		
				clock_t start_time = clock();
				double *v = createArray(n);

				clock_t mid_time = clock();
				double err;
				sum = calcSum(v, n, S, &err);
				free(v);
				clock_t end_time = clock();
		
				double init_time = (mid_time - start_time)/(double)CLOCKS_PER_SEC;
				double sum_time = (end_time - mid_time)/(double)CLOCKS_PER_SEC;
				
				init_time_avg += init_time;
				sum_time_avg += sum_time;
				err_avg += err;
				err_avg2 += err*err;

				
			} 
			init_time_avg /= n_avg;
			sum_time_avg /= n_avg;
			err_avg /= n_avg;
			err_avg2 /= n_avg;
			
			char str[80];
			getSizeString(((uint64_t)1<<k)*8, str);

			printf("k = %3d, n = %10lu, sum = %f, time_init = %e, time_sum = %e, err = %e +/- %e, mem = %s\n", k, n, sum, init_time_avg, sum_time_avg, err_avg, sqrt(fabs(err_avg2 - err_avg*err_avg)), str);

			
			fprintf(fp, "%lu %e %e %e %e\n", n, init_time_avg, sum_time_avg, err_avg, sqrt(fabs(err_avg2 - err_avg*err_avg)));
	
		}
		fclose(fp);
	} else {

		clock_t start_time = clock();
		int k = atoi(argv[1]);
		uint64_t n = (uint64_t)1 << k;
		double *v = createArray(n);

		double err;
		double sum = calcSum(v, n, S, &err);
		clock_t end_time = clock();

		double total_time = (end_time-start_time)/(double)CLOCKS_PER_SEC;
		//Print the result
		printResult(k, sum, n, total_time);

	}	
	
	return 0;
}

