#include<stdio.h>	//needed for printf
#include<stdlib.h>	//needed for malloc(), atoi()
#include<stdint.h>	//needed for uint64_t
#include <mpi.h> 	//needed for MPI functions
#include "utils.h"	//needed for printResult()

int main(int argc, char **argv){
	double start_time, end_time, total_time;
	start_time = MPI_Wtime();

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
	int k = atoi(argv[1]);
	uint64_t n = (uint64_t)1 << k;
	int offset = n%nprocs; // number of elements left over after evenly distribution
	int np = n/nprocs + (offset > rank ? 1 : 0);
	int tag = 1;
	
	//Allocate partial vector for each process. Note that this result in one
	//redundant element on some of the processes in the case where n%procs != 0
	double *v_p = malloc(np*sizeof(double));

	if(rank == 0){
		//Compute the elements of v
		int np2;
		uint64_t i;
		for(int rank2 = 1; rank2 < nprocs; rank2++){
			np2 = n/nprocs + (offset > rank2 ? 1: 0);
			
//			#pragma omp parallel for schedule(static)
			for(uint64_t j = 0; j < np2; j++){
				i = rank2 + j*nprocs + 1;
				v_p[j] = 1/(double)(i*i);
			}
			MPI_Send(v_p, np2, MPI_DOUBLE, rank2, tag, MPI_COMM_WORLD);
		}
//		#pragma omp parallel for schedule(static)
		for(uint64_t j = 0; j < np; j++){
			i = j*nprocs + 1;
			v_p[j] = 1/(double)(i*i);
		}
	}else
		MPI_Recv(v_p, np, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);

	//Compute the partial sum S_n
	double S_n_p = 0;
//	#pragma omp parallel for reduction(+:S_n_p)
	for(uint64_t i = np; i > 0; i--)
		S_n_p += v_p[i-1];

	double S_n;
	MPI_Reduce(&S_n_p, &S_n, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	//Print the result	
	end_time = MPI_Wtime();
	total_time = end_time-start_time;

	if(rank == 0)
		printResult(k, S_n, np, total_time);

	MPI_Finalize();

	return 0;
}

