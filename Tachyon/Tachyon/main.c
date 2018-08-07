#include "params.h"
#include "blake2.h"
#include "aes.h"
#include "ntt.h"
#include "gck.h"
#include "math.h"




int main(int argc, char **argv)
{
	double timeSign, timeVer, timeAdd;
	timeSign = 0.0;
	timeVer = 0.0;
	timeAdd = 0.0;
	clock_t start, start2;
	clock_t end, end2;
	uint8_t shift;
	unsigned char sk[16] = {0x54, 0xa2, 0xf8, 0x03, 0x1d, 0x18, 0xac, 0x77, 0xd2, 0x53, 0x92, 0xf2, 0x80, 0xb4, 0xb1, 0x2f};
//	unsigned char sk[16] = {0xac, 0xf1, 0x29, 0x3f, 0x3a, 0xe6, 0x77, 0x7d, 0x74, 0x15, 0x67, 0x91, 0x99, 0x53, 0x69, 0xc5};

	block key;
	block* prf_out;
	unsigned char* prf_out2;
	prf_out = malloc(16*16);
	prf_out2 = malloc(16*16);
	
	

	uint64_t ii ,i;
	ii = 1;
	i = 0;

	//CHANGED FROM 32 TO 64 BIT UINT
	//xi, temp, rPrime
	
	uint64_t *xi; // this is a 0/1 input array to gck function
	uint32_t *yi;
	uint32_t vPrime[N] = {0};
	uint32_t rHat[N] = {0};
	uint64_t reject = 0;
	uint64_t verified = 0;
	uint8_t rejected = 0;
	xi = malloc(N*mu*T*sizeof(uint64_t));
	memset(xi, 0, N*mu*T*sizeof(uint64_t));
	yi = malloc(N*T*sizeof(uint32_t));
	memset(yi, 0, N*T*sizeof(uint32_t));
	
	uint32_t rPrime[N*mu];
	uint64_t signature[N*mu];
	uint64_t temp[N*mu];
	uint32_t r[N];
	unsigned char rHash[N*4];
	block cipher[N*mu/4];
	uint8_t signatureHash[64];
	uint8_t signatureHash2[64];
	uint8_t indexes[64];
	uint8_t message[2] = {0};
	uint8_t concatenated[66] = {0};
	
	key = toBlock((uint8_t*)sk);
	setKey(key);
	uint64_t index;
	uint64_t counter = 1025;

	
//	uint8_t* fastRejection;
//	fastRejection = malloc(XI+K);
//	for(i = 0; i < K; i++){
//		//fastRejection[i] = 1;
//		printf("%u, ", 1);
//	}
//	for(i = K; i < upperLower+K; i++){
//		//fastRejection[i] = 0;
//		printf("%u, ", 0);
//	}
//	for(i = upperLower+K; i < XI+K; i++){
//		//fastRejection[i] = 1;
//		printf("%u, ", 1);
//	}
//	printf("};\n");
	
	
	
	
	
	//Key Generation==========================================================================
	for(i = 0; i < T; i++){
		ecbEncCounterMode(i,16,prf_out);
		memcpy(prf_out2, prf_out, 256);
		
		for (unsigned int j = 0 ; j<256; j++){
			shift = (uint8_t)prf_out2[j];
			for (unsigned int k = 0 ; k<8; k++){
				xi[N*mu*i + 8*j + k] = bitRead(shift);
				shift = shiftOne(shift);
			}
		}
		
		gck_ntt64(xi + N*mu*i);
		gck_linearComb64(xi + N*mu*i, yi + N*i);
		
	}
	
for(ii = 0; ii < 10000; ii++){	
	//Signature Generation =================================================================
	start = clock();
	ecbEncCounterMode(counter,N*mu/4,cipher);
	memcpy(rPrime, cipher, N*mu*4);
	for(i = 0; i<N*mu; i++){
		rPrime[i] = rPrime[i]%XI;
		temp[i] = rPrime[i];
	}
	counter++;
	
	
	gck_ntt64(temp);
	gck_linearComb64(temp, r);
	
	block mask = _mm_set_epi8(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	
//	memcpy(rHash, r, N*4);
	blake2b(signatureHash, r, NULL, 64, N*4, 0);
	memcpy(concatenated + 2, signatureHash, 64);
	blake2b(indexes, concatenated, NULL, 64, 66, 0);
	for(i = 0; i<K; i++){
		index = (indexes[2*i] + indexes[2*i+1]*256)%T;
		ecbEncCounterMode(index,16,prf_out);
		
//		memcpy(prf_out2, prf_out, 256);
		
//		for (unsigned int j = 0 ; j<256; j++){
//			shift = (uint8_t)prf_out2[j];
//			for (unsigned int k = 0 ; k<8; k++){
//				rPrime[8*j + k] += bitRead(shift);
//				shift = shiftOne(shift);
//			}
//		}

		for(int h =0; h < 8; ++h){
			block b[16];
			b[ 0] = _mm_and_si128(prf_out[ 0], mask);
			b[ 1] = _mm_and_si128(prf_out[ 1], mask);
			b[ 2] = _mm_and_si128(prf_out[ 2], mask);
			b[ 3] = _mm_and_si128(prf_out[ 3], mask);
			b[ 4] = _mm_and_si128(prf_out[ 4], mask);
			b[ 5] = _mm_and_si128(prf_out[ 5], mask);
			b[ 6] = _mm_and_si128(prf_out[ 6], mask);
			b[ 7] = _mm_and_si128(prf_out[ 7], mask);
			b[ 8] = _mm_and_si128(prf_out[ 8], mask);
			b[ 9] = _mm_and_si128(prf_out[ 9], mask);
			b[10] = _mm_and_si128(prf_out[10], mask);
			b[11] = _mm_and_si128(prf_out[11], mask);
			b[12] = _mm_and_si128(prf_out[12], mask);
			b[13] = _mm_and_si128(prf_out[13], mask);
			b[14] = _mm_and_si128(prf_out[14], mask);
			b[15] = _mm_and_si128(prf_out[15], mask);
			
			for(int j = 0; j < 16;++j){
				char* bb = (char*)&(b[j]);
				rPrime[j * 128 + 8 * 0 + h] +=  bb[0];
				rPrime[j * 128 + 8 * 1 + h] +=  bb[1];
				rPrime[j * 128 + 8 * 2 + h] +=  bb[2];
				rPrime[j * 128 + 8 * 3 + h] +=  bb[3];
				rPrime[j * 128 + 8 * 4 + h] +=  bb[4];
				rPrime[j * 128 + 8 * 5 + h] +=  bb[5];
				rPrime[j * 128 + 8 * 6 + h] +=  bb[6];
				rPrime[j * 128 + 8 * 7 + h] +=  bb[7];
				rPrime[j * 128 + 8 * 8 + h] +=  bb[8];
				rPrime[j * 128 + 8 * 9 + h] +=  bb[9];
				rPrime[j * 128 + 8 * 10 + h] +=  bb[10];
				rPrime[j * 128 + 8 * 11 + h] +=  bb[11];
				rPrime[j * 128 + 8 * 12 + h] +=  bb[12];
				rPrime[j * 128 + 8 * 13 + h] +=  bb[13];
				rPrime[j * 128 + 8 * 14 + h] +=  bb[14];
				rPrime[j * 128 + 8 * 15 + h] +=  bb[15];
			}
			prf_out[ 0] = _mm_srli_epi64(prf_out[ 0], 1);
			prf_out[ 1] = _mm_srli_epi64(prf_out[ 1], 1);
			prf_out[ 2] = _mm_srli_epi64(prf_out[ 2], 1);
			prf_out[ 3] = _mm_srli_epi64(prf_out[ 3], 1);
			prf_out[ 4] = _mm_srli_epi64(prf_out[ 4], 1);
			prf_out[ 5] = _mm_srli_epi64(prf_out[ 5], 1);
			prf_out[ 6] = _mm_srli_epi64(prf_out[ 6], 1);
			prf_out[ 7] = _mm_srli_epi64(prf_out[ 7], 1);
			prf_out[ 8] = _mm_srli_epi64(prf_out[ 8], 1);
			prf_out[ 9] = _mm_srli_epi64(prf_out[ 9], 1);
			prf_out[10] = _mm_srli_epi64(prf_out[10], 1);
			prf_out[11] = _mm_srli_epi64(prf_out[11], 1);
			prf_out[12] = _mm_srli_epi64(prf_out[12], 1);
			prf_out[13] = _mm_srli_epi64(prf_out[13], 1);
			prf_out[14] = _mm_srli_epi64(prf_out[14], 1);
			prf_out[15] = _mm_srli_epi64(prf_out[15], 1);
			
			
			
		}
	}
	
//	for(i = 0; i<N*mu; i++)
//		rejected += fastRejection[rPrime[i]];
//	if(rejected != 0)
//		reject++;
	
	i=0;
	while(i<N*mu && rejected == 0){
		//if((rPrime[i] > maxR || rPrime[i] < K) && rejected == 0){
		if(rPrime[i]-K>=upperLower){
			reject++;
			rejected = 1;
		}
		i++;
	}
	
	
	
	
	end = clock();
	rejected = 0;
	timeSign = timeSign + (double)(end-start);
	
	
	for(i = 0; i<N*mu; i++)
		signature[i] = rPrime[i];
	
	//Signature Verification=====================================
	start2 = clock();
	i=0;
	while(i<N*mu && rejected == 0){
		//if((rPrime[i] > maxR || rPrime[i] < K) && rejected == 0){
		if(rPrime[i]-K>=upperLower){
			rejected = 1;
		}
		i++;
	}
	
//if(!rejected){
	blake2b(indexes, concatenated, NULL, 64, 66, 0);
	
	for(i = 0; i<K; i++){
		index = (indexes[2*i] + indexes[2*i+1]*256)%T;
		for (unsigned j = 0 ; j<N; j++){	
			vPrime[j] = (vPrime[j] + yi[index*N+j])%Q;
		}
	}
	
	gck_ntt64(signature);
	gck_linearComb64(signature, rHat);
	
	for (unsigned j = 0 ; j<N; j++){
		rHat[j] = (rHat[j] + Q - vPrime[j])%Q;
	}
	
	//	memcpy(rHash, r, N*4);
	blake2b(signatureHash2, rHat, NULL, 64, N*4, 0);
	
	if (memcmp(signatureHash,signatureHash2,64) == 0)
		verified++;
//}
	rejected = 0;
	end2 = clock();
	timeVer = timeVer + (double)(end2-start2);
	
	memset(vPrime, 0, N*sizeof(uint32_t));
}	
	printf("%lu signatures out of %lu signatures are rejected\n", reject, ii);
	printf("%lu signatures out of %lu signatures are verified\n", verified, ii);
	printf("%fus per signature generation\n", ((double) (timeSign * 1000 * 1000)) / CLOCKS_PER_SEC / ii);
	printf("%fus per verification \n", ((double) (timeVer * 1000 * 1000)) / CLOCKS_PER_SEC / ii );
	
	free(prf_out);
	free(prf_out2);
	free(xi);
	free(yi);
	return 0;
}
