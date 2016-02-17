#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

static const double PI = 3.14159265358979323846;

int main(int argc, char **argv){
	
	int nprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(argc != 2){
		if(rank == 0)
			printf("Input argument k was missing!\n\n");
		MPI_Finalize();
		return 1;
	}	

	MPI_Status status;

	//Initialize
	size_t i, j;
	
	int k = atoi(argv[1]);
	int n = (int)pow(2,k);
	int np = n/nprocs + (n%nprocs >= rank+1 ? 1 : 0);
	int tag = 1;

	//Allocate memory (this is valid C99)
	double v_p[np];
	if(rank == 0){
		//Compute the elements of v
		int np2, rank2;
		for(rank2 = 1; rank2 < nprocs; rank2++){
			np2 = n/nprocs + (n%nprocs >= rank2+1 ? 1: 0);
			double v_p_temp[np2];
			#pragma omp parallel for schedule(static) 			
			for(j = 0; j < np2; j++){
				i = rank2+j*nprocs+1;
				v_p_temp[j] = 1/(double)(i*i);
			}
			MPI_Send(v_p_temp, np2, MPI_DOUBLE, rank2, tag, MPI_COMM_WORLD);
		}	
		#pragma omp parallel for schedule(static)
		for(j = 0; j < np; j++){
			i = j*nprocs+1;
			v_p[j] = 1/(double)(i*i);
		}
	}else
		MPI_Recv(v_p, np, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);

	//Compute the partial sum S_n
	double S_n_p = 0;
	#pragma omp parallel for reduction(+:S_n_p)
	for(size_t i = 0; i < np; i++)
		S_n_p += v_p[i];
	
	double S_n;
	MPI_Reduce(&S_n_p, &S_n, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
		//Print the result
		double S = PI*PI/6;
		printf("|S-S_%d| = %.17g\n\n", n, fabs(S_n - S));
	}

	MPI_Finalize();
	return 0;
}

