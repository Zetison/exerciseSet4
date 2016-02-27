The program should be compiled together with cmake as follows

----------------------------------------------------------------------------
> mkdir build
> cd build
> cmake ..
> make
----------------------------------------------------------------------------

One is then able to run the bash scripts exercise3.sh and exercise6.sh. 
For the script exercise3.sh, the first and second argument should be 
the range of k values to be analyzed and the third argument should be 
the number of processes to be used in the MPI implementatione 

The results in the report is obtained by the following continuation

----------------------------------------------------------------------------
> cd ..
> exercise3.sh 3 31 24
> exercise6.sh
----------------------------------------------------------------------------

Note that the program ran on markov with a lot of memory available (256GB)
such that one was able to simulate k=31 (requiring 17GB of memory in the 
serial kode)
