#include "gck.h"


void gck_ntt(uint32_t input[N*mu]){
	unsigned int i;

	for (i = 0; i < mu; i++, input += N)
	{
		ntt(input);
	}
}


//const uint16_t *a, 
void gck_linearComb(const uint32_t input[N*mu], uint32_t result[N])
{
	int i, j;

	for (j = 0; j < N; ++j)
	{
		register uint32_t sum = 0;
		const register uint32_t *f = input + j;
		const register uint32_t *k = As + j;

		for (i = 0; i < mu; i++, f += N,k += N)
		{
			sum += (*f) * (*k);
		}

		result[j] = (sum)%Q;
	}

}