#include <stdint.h>
#include <wmmintrin.h>

// Encrypts the vector of blocks {baseIdx, baseIdx + 1, ..., baseIdx + length - 1} 
// and writes the result to cyphertext.
typedef  __m128i block;
block mRoundKey[11];

void ecbEncCounterMode(uint64_t baseIdx, uint64_t length, block* cyphertext);
void setKey(block userKey);

