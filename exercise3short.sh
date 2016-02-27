#! /bin/sh
mkdir -p results

P=$1
outputfilename=results/exercise3_table.txt
printf "k Serial OpenMP MPI\n" > $outputfilename 

count=1
declare -a arr=("compute_S" "compute_S_OpenMP" "compute_S_MPI")
for k in 3 14 31; do
	printf $k" " >> $outputfilename
	for filename in "${arr[@]}"; do
		printf "Running k number "$count" of 3 for "$filename"\n"
		if [ $filename == "compute_S" ]; then
			./build/$filename $k > temp.txt
		elif [ $filename == "compute_S_OpenMP" ]; then
			./build/$filename $k > temp.txt
		elif [ $filename == "compute_S_MPI" ]; then
			mpiexec -n $P ./build/$filename $k > temp.txt
		fi

		tempString="$(sed -n 3,3p temp.txt)"
		tempStringArr=( $tempString )
		printf ${tempStringArr[2]}" " >> $outputfilename
	done
	printf "\n" >> $outputfilename
	((count+=1))	
done
rm temp.txt
