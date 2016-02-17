#include<stdint.h>


uint64_t powerOfTwo(int n){
	uint64_t result = 1;
	for(int i = 0; i < n; i++)
		result *= 2;
	return result;
}
