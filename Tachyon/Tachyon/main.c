#include "params.h"
#include "blake2.h"
#include "aes.h"
#include "ntt.h"

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
	block key;
	block* prf_out;
	unsigned char* prf_out2;
	prf_out = malloc(16*16);
	prf_out2 = malloc(16*16);

	uint64_t ii ,i;
	ii = 0;
	i = 0;
	int pos = 0;
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
	//=================
	
	unsigned char xi[N*mu*T] = {0}; // this is a 0/1 input array to gck function
	
	unsigned char prfin[N];
	unsigned char prfout[N];
	
	key = toBlock((uint8_t*)sk);
	setKey(key);
	
	ecbEncCounterMode(c,16,prf_out);
	memcpy(prf_out2, prf_out, 256);
	
	printf("prf_out: ");
	for (int i = 0; i < 256; i++) {
	  printf("%x", prf_out2[i]);
	}
	printf("\n");
	
	ecbEncCounterMode(a,16,prf_out);
	memcpy(prf_out2, prf_out, 256);
	
	printf("prf_out: ");
	for (int i = 0; i < 256; i++) {
	  printf("%x", prf_out2[i]);
	}
	printf("\n");
	
	memset(prfin, 0, N);
	memset(prfout, 0, N);
	
	start = clock();
	for(ii = 0; ii < 1000000; ii++){
		ecbEncCounterMode(ii,16,prf_out);
		memcpy(prf_out2, prf_out, 256);
	}
	end = clock();
	timeAdd = timeAdd + (double)(end-start);
	printf("%fus per AES 16 blocks (generate 2048 bits) \n", ((double) (timeAdd * 1000)) / CLOCKS_PER_SEC / ii * 1000);
	
	
	
	
	
	//Key Generation
	start = clock();
	for(i = 0; i < T; i++){
		ecbEncCounterMode(i,16,prf_out);
		memcpy(prf_out2, prf_out, 256);
		
		for (unsigned j = 0 ; j<256; j++){
			shift = (uint8_t)prf_out2[j];
			for (unsigned k = 0 ; k<8; k++){
				xi[2048*i + 8*j + k] = bitRead(shift);
				shift = shiftOne(shift);
			}
		}
	}
	end = clock();
	timeVer = timeVer + (double)(end-start);
	printf("%fus per AES 16 blocks (generate xi bits) \n", ((double) (timeVer * 1000 * 1000)) / CLOCKS_PER_SEC /  T );
	
//	printf("prf_out: ");
//	for (int i = 0; i < 2048; i++) {
//	  printf("%x", xi[i]);
//	}
//	printf("\n");
	
	free(prf_out);
	free(prf_out2);
	return 0;
}
