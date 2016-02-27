#! /bin/sh
mkdir -p results
filename=results/exercise6.txt
printf "k MPI_1 MPI_2 MPI_8\n" > $filename

count=1
for k in 3 14 31; do
	printf "\nRunning compute_S_MPI "$count" of 3 times\n"
	printf $k" " >> $filename
	for P in 1 2 8; do
		mpiexec -n $P ./build/compute_S_MPI $k > temp.txt
		tempString="$(sed -n 3,3p temp.txt)"
		tempStringArr=( $tempString )
		printf ${tempStringArr[2]}" " >> $filename
	done
	printf "\n" >> $filename
	((count+=1))	
done
rm temp.txt
