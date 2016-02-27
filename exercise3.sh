#! /bin/sh
# The first input argument is k_start, the second is k_end and
# the third input number is the number of processes used in the MPI implementation

mkdir -p results
k_start=$1
k_end=$2
P=$3
declare -a arr=("compute_S" "compute_S_OpenMP" "compute_S_MPI")
count=1
for filename in "${arr[@]}"; do
	> "results/exercise3_plot_"$filename".txt"
	printf "\nRunning program "$count" of 3\n"
	for (( k=$k_start; k<=$k_end; k++ )); do
		#run given program(filename) for given k
		if [ $filename == "compute_S" ]; then
			./build/$filename $k > temp.txt
		elif [ $filename == "compute_S_OpenMP" ]; then
			./build/$filename $k > temp.txt
		elif [ $filename == "compute_S_MPI" ]; then
			mpiexec -n $P ./build/$filename $k > temp.txt
		fi
		
		
		#print result to file (include header if k = k_start)
		if [ $k == $k_start ]; then
			tempString="$(sed -n 2,3p temp.txt)\n"
		else
			tempString="$(sed -n 3,3p temp.txt)\n"
		fi
		printf "$tempString"
		printf "$tempString" >> "results/exercise3_plot_"$filename".txt"
	done
	((count+=1))
done
rm temp.txt
