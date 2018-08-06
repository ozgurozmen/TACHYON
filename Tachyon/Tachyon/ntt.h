#include "params.h"

uint32_t montgomery_reduce(uint64_t a);

void ntt(uint32_t p[N]);
void ntt64(uint64_t p[N]);