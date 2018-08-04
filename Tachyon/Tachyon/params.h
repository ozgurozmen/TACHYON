#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#include <stdint.h>

#ifndef PARAMS_H
#define PARAMS_H

#ifndef MODE
#define MODE 0
#endif

#define N 256U
#define mu 8U

#if MODE == 0
#define Q 134215681U
#define QINV 130021375U
#define T 1024U
#define K 18U
static const uint32_t zetas[N] = {0, 30975076};


#elif MODE == 1
#define Q 1073479681U
#define QINV 1073479679U
#define T 2048U
#define K 25U
static const uint32_t zetas[N] = {0, 153222134};


#elif MODE == 2
#define Q 2147483137U
#define QINV 2013003263U
#define T 3072U
#define K 32U
static const uint32_t zetas[N] = {0, 578487198};


#endif

#define BIT_SET(character, position) ((*character |= 1 << position))	
#define BIT_CLEAR(character, position) ((*character &= ~(1 << position)))
#define BIT_TOGGLE(character, position)	((*character ^= 1 << position))
#define BIT_CHECK(var,pos) !!((*var) & (1<<(pos)))

#define bitRead(value) ((value) & 0x01)
#define shiftOne(value) ((value) >> 1)

#endif
