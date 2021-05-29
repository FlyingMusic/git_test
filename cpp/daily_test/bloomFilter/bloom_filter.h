#ifndef __PACHIRA_BLOOM_FILTER_H__
#define __PACHIRA_BLOOM_FILTER_H__

#include<stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int (*hashfunc_t)(const char *, unsigned int len);

typedef struct {
	size_t asize;
	unsigned char *a; //to store the state of existence bits 
	size_t nfuncs;
	hashfunc_t *funcs; // hash funcs
} BLOOM;

BLOOM *bloom_create(size_t size, size_t nfuncs, ...);
int bloom_destroy(BLOOM *bloom);
int bloom_add(BLOOM *bloom, const char *s, unsigned int len);
int bloom_check(BLOOM *bloom, const char *s, unsigned int len);


#ifdef __cplusplus
};
#endif

#endif
