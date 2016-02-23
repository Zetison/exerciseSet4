#include <mpi.h> 	//needed for MPI functions
#include "utils.h"	//needed for printResult()
#include <omp.h>	//needed for printResult()

int main(int argc, char **argv){
	double start_time, end_time, total_time;
	start_time = MPI_Wtime();

	int nprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//#pragma omp parallel for
	//for (int i = 0; i < 1; i++)
		//printf("num threads = %d\n", omp_get_num_threads()); fflush(stdout);

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
		for(int rank2 = 1; rank2 < nprocs; rank2++){
			int np2 = n/nprocs + (offset > rank2 ? 1: 0);
			
			#pragma omp parallel for schedule(static)
			for(uint64_t j = 0; j < np2; j++){
				uint64_t i = rank2 + j*nprocs + 1;
				v_p[j] = 1/(double)(i*i);
			}
			MPI_Send(v_p, np2, MPI_DOUBLE, rank2, tag, MPI_COMM_WORLD);
			//printf("send to rank %d\n", rank2); fflush(stdout);;
		}
		#pragma omp parallel for schedule(static)
		for(uint64_t j = 0; j < np; j++){
			uint64_t i = j*nprocs + 1;
			v_p[j] = 1/(double)(i*i);
		}
		//printf("rank0 done\n"); fflush(stdout);
	}else {
		MPI_Recv(v_p, np, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
		//printf("rank %d recv\n", rank); fflush(stdout);
	}

	double mid_time = MPI_Wtime();

	//Compute the partial sum S_n
	double S_n_p = 0;
	#pragma omp parallel for reduction(+:S_n_p)
	for(int64_t i = np-1; i >= 0; i--)
		S_n_p += v_p[i];

	double S_n;
	//printf("Reduce rank %d\n", rank); fflush(stdout);
	MPI_Reduce(&S_n_p, &S_n, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	//printf("Done reduce rank %d\n", rank); fflush(stdout);

	//Print the result	
	end_time = MPI_Wtime();
	total_time = end_time-start_time;

	if(rank == 0)
		printResult(k, S_n, np, total_time);

	printf("rank %d: %f %f %f\n", rank, mid_time-start_time, end_time-mid_time, end_time-start_time);

	MPI_Finalize();

	return 0;
}

