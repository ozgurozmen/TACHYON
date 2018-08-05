#include "params.h"
#include "blake2.h"
#include "aes.h"
#include "ntt.h"
#include "gck.h"
//#include "iaes_asm_interface.h"
//#include "iaesni.h"

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
//	int pos = 0;
	//=================
//	uint64_t a,b,c;
//	a = 578487198;
//	b = 1;
//	c = a*b%Q;
//	
//	printf("{");
//	for (ii = 0; ii < N-1; ++ii) {
//		b = b*a%Q;
//		printf("%lu, ", b);
//	}
//	printf("};\n");
	
//	uint32_t random[N*mu];
//	block cipher[512];
//	ecbEncCounterMode(1,512,cipher);
//	memcpy(random, cipher, 8192);
//	printf("As[N*mu] = {");
//	for (int i = 0; i < 2048; i++) {
//	  printf("%u, ", random[i]%Q);
//	}
//	printf("};\n");
	
	//=================
	
	uint32_t *xi; // this is a 0/1 input array to gck function
	uint32_t yi[N*T] = {0};
	uint64_t reject = 0;
	xi = malloc(N*mu*T*sizeof(uint32_t));
	memset(xi, 0, N*mu*T*sizeof(uint32_t));
	
	uint32_t rPrime[N*mu];
	uint32_t temp[N*mu];
	uint32_t r[N];
	unsigned char rHash[N*4];
	block cipher[N*mu/4];
	uint8_t signatureHash[64];
	uint8_t indexes[64];
	uint8_t message[2] = {0};
	uint8_t concatenated[66] = {0};
	
	key = toBlock((uint8_t*)sk);
	setKey(key);
	uint64_t index;
	uint64_t counter = 1025;

	

//	start = clock();
//	for(ii = 0; ii < 1000000; ii++){
//		ecbEncCounterMode(ii,16,prf_out);
//		memcpy(prf_out2, prf_out, 256);
//	}
//	end = clock();
//	timeAdd = timeAdd + (double)(end-start);
//	printf("%fus per AES 16 blocks (generate 2048 bits) \n", ((double) (timeAdd * 1000)) / CLOCKS_PER_SEC / ii * 1000);
	
	
	
	
	
	//Key Generation
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
		
		gck_ntt(xi + N*mu*i);
		gck_linearComb(xi + N*mu*i, yi + N*i);
		
	}
	
for(ii = 0; ii < 100000; ii++){	
	//Signature Generation - Sample r' first, add to x_i's and then do the rejection sampling here. Only calculate F_A once.
	start = clock();
	ecbEncCounterMode(counter,N*mu/4,cipher);
	memcpy(rPrime, cipher, N*mu*4);
	memcpy(temp, cipher, N*mu*4);
	counter++;
	
	gck_ntt(temp);
	gck_linearComb(temp, r);
	
	memcpy(rHash, r, N*4);
	blake2b(signatureHash, r, NULL, 64, 64, 0);
	memcpy(concatenated + 2, signatureHash, 64);
	blake2b(indexes, concatenated, NULL, 64, 66, 0);
	for(i = 0; i<K; i++){
		index = (indexes[2*i] + indexes[2*i+1]*256)%1024;
		ecbEncCounterMode(index,16,prf_out);
		memcpy(prf_out2, prf_out, 256);
		
		for (unsigned int j = 0 ; j<256; j++){
			shift = (uint8_t)prf_out2[j];
			for (unsigned int k = 0 ; k<8; k++){
				rPrime[8*j + k] += bitRead(shift);
				shift = shiftOne(shift);
			}
		}
	}
	
	
	end = clock();
	timeSign = timeSign + (double)(end-start);
	//Signature Verification
	start = clock();

	
	end = clock();
	timeVer = timeVer + (double)(end-start);
}	
	
	printf("%fus per signature generation\n", ((double) (timeSign * 1000 * 1000)) / CLOCKS_PER_SEC / ii);
	printf("%fus per verification \n", ((double) (timeVer * 1000 * 1000)) / CLOCKS_PER_SEC / ii );
	
	free(prf_out);
	free(prf_out2);
	free(xi);
	return 0;
}
