#include "gck.h"


void gck_ntt(uint32_t input[N*mu]){
	unsigned int i;

	for (i = 0; i < mu; i++, input += N)
	{
		ntt(input);
	}
}

void gck_ntt64(uint64_t input[N*mu]){
	unsigned int i;

	for (i = 0; i < mu; i++, input += N)
	{
		ntt64(input);
	}
}


//const uint16_t *a, 
void gck_linearComb(const uint32_t input[N*mu], uint32_t result[N]){
	unsigned int i, j;

	for (j = 0; j < N; ++j)
	{
		unsigned long long sum = 0;
		const register uint32_t *f = &input[j];
		const register uint32_t *k = &As[j];

		for (i = 0; i < mu; i++, f += N,k += N)
		{
			sum += ((uint64_t)(*f) * (*k));
		}

		result[j] = (sum)%Q;
	}

}

void gck_linearComb64(const uint64_t input[N*mu], uint32_t result[N]){
	unsigned int i, j;

	for (j = 0; j < N; ++j)
	{
		//__uint128_t sum = 0;
		uint64_t sum = 0;
		const register uint64_t *f = &input[j];
		const register uint32_t *k = &As[j];

		for (i = 0; i < mu; i++, f += N,k += N)
		{
			//(__uint128_t)
			//_umul128(takes two uint64_t, gives output of unsigned long long
			
			//lazy reduction, do a few and then reduce.
			if(MODE == 0)
				sum += ((*f) * (*k)); //this unsigned long long does not do anything.
			else
				sum += ((*f) * (*k))%Q;
		}

		result[j] = (sum);
	}

}