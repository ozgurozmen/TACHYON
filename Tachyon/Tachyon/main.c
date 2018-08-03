#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#include "params.h"
#include "blake2.h"
#include "aes.h"

//#include "iaes_asm_interface.h"
//#include "iaesni.h"

#include "math.h"

static const uint32_t zetas[N] = {0};

uint32_t montgomery_reduce(uint64_t a) {
  const uint64_t qinv = QINV; //QINV =  -q^(-1) mod 2^32
  uint64_t t;

  t = a * qinv;
  t &= (1ULL << 32) - 1;
  t *= Q;
  t = a + t;
  return t >> 32;
}

void ntt(uint32_t p[N]) {
  unsigned int len, start, j, k;
  uint32_t zeta, t;

  k = 1;
  for(len = 128; len > 0; len >>= 1) {
    for(start = 0; start < N; start = j + len) {
      zeta = zetas[k++]; // zetas -> /* Roots of unity in order needed by forward ntt */
      for(j = start; j < start + len; ++j) {
        t = montgomery_reduce((uint64_t)zeta * p[j + len]);
        p[j + len] = p[j] + 2*Q - t;
        p[j] = p[j] + t;
      }
    }
  }
}


int main(int argc, char **argv)
{
	double timeSign, timeVer, timeAdd;
	timeSign = 0.0;
	timeVer = 0.0;
	timeAdd = 0.0;
	clock_t start, start2;
	clock_t end, end2;
	unsigned char sk[16] = {0x54, 0xa2, 0xf8, 0x03, 0x1d, 0x18, 0xac, 0x77, 0xd2, 0x53, 0x92, 0xf2, 0x80, 0xb4, 0xb1, 0x2f};
	block key;
	block* prf_out;
	unsigned char* prf_out2;
	prf_out = malloc(8*16);
	prf_out2 = malloc(8*16);

	uint64_t ii;
	int pos = 0;
	//=================
	uint64_t a,b,c;
	a = 2147483648;
	b = 2147483648;
	c = a*b%Q;
	printf("c = %lu", c);
	
	for (ii = 0; ii < mu; ++ii) {
		printf("hello world\n");
	}
	//=================
	
	unsigned char xi[N*mu*T] = {0}; // this is a 0/1 input array to gck function
	
	unsigned char prfin[N];
	unsigned char prfout[N];
	
	key = toBlock((uint8_t*)sk);
	setKey(key);
	
	ecbEncCounterMode(c,8,prf_out);
	memcpy(prf_out2, prf_out, 128);
	
	printf("prf_out: ");
	for (int i = 0; i < 128; i++) {
	  printf("%x", prf_out2[i]);
	}
	printf("\n");
	
	ecbEncCounterMode(a,8,prf_out);
	memcpy(prf_out2, prf_out, 128);
	
	printf("prf_out: ");
	for (int i = 0; i < 128; i++) {
	  printf("%x", prf_out2[i]);
	}
	printf("\n");
	
	memset(prfin, 0, N);
	memset(prfout, 0, N);
	
	start = clock();
	for(ii = 0; ii < 1000000; ii++){
		ecbEncCounterMode(ii,8,prf_out);
		memcpy(prf_out2, prf_out, 128);
	}
	end = clock();
	timeAdd = timeAdd + (double)(end-start);
	printf("%fus per AES 8 blocks (generate 1024 bits) \n", ((double) (timeAdd * 1000)) / CLOCKS_PER_SEC / ii * 1000);
	//Key Generation
	for(ii = 0; ii < T; ii++){
		
	}
	
	
	
	return 0;
}
