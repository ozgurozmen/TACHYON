#include "gck.h"


void gck_ntt(uint32_t input[N*mu]){
	unsigned int i;

	for (i = 0; i < mu; i++, input += N)
	{
		ntt(input);
	}
}


void gck_linearComb(const uint32_t *input, int m, const uint16_t *a, uint32_t result[N])
{
	int i, j;

	for (j = 0; j < N; ++j)
	{
		register uint32_t sum = 0;
		const register int32_t *f = input + j;
		const register int16_t *k = a + j;

		for (i = 0; i < m; i++, f += N,k += N)
		{
			sum += (*f) * (*k);
		}

		result[j] = (sum)%Q;
	}

//	for (j = 0; j < N; ++j)
//	{
//		result[j] = ((FIELD_SIZE << 22) + result[j]) % FIELD_SIZE;
//	}
}