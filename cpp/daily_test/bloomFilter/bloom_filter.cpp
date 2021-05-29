#include<limits.h>
#include<stdarg.h>

#include "bloom_filter.h"
#include "pachira_mem.h"
#include "dlog.h"
#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

BLOOM *bloom_create(size_t size, size_t nfuncs, ...){
	BLOOM *bloom;
	va_list l;
	int n;

	if(!(bloom=(BLOOM *)PACHIRA_MALLOC(sizeof(BLOOM)))){
        LOG_ERROR("bloom malloc failed.");
        return NULL;
    }

	// ceil the number of char to malloc for the bloom
    int bit_size = (size + CHAR_BIT - 1) / CHAR_BIT * sizeof(unsigned char);
	if(!(bloom->a = (unsigned char*)PACHIRA_MALLOC(bit_size))){
        LOG_ERROR("bloom a malloc failed.");
		PACHIRA_FREE(bloom);
		return NULL;
	}
	if(!(bloom->funcs = (hashfunc_t*)PACHIRA_MALLOC(nfuncs * sizeof(hashfunc_t)))){
        LOG_ERROR("bloom funcs malloc failed.");
		PACHIRA_FREE(bloom->a);
		PACHIRA_FREE(bloom);
		return NULL;
	}

	va_start(l, nfuncs);
	for(n = 0; n < nfuncs; ++n){
		bloom->funcs[n] = va_arg(l, hashfunc_t);
	}
	va_end(l);

	bloom->nfuncs = nfuncs;
	bloom->asize = size;

	return bloom;
}

int bloom_destroy(BLOOM *bloom){
	PACHIRA_FREE(bloom->a);
	PACHIRA_FREE(bloom->funcs);
	PACHIRA_FREE(bloom);

	return 0;
}

int bloom_add(BLOOM *bloom, const char *s, unsigned int len){
	size_t n;
	for(n = 0; n < bloom->nfuncs; ++n) {
		SETBIT(bloom->a, bloom->funcs[n](s, len) % bloom->asize);
	}
	return 0;
}

int bloom_check(BLOOM *bloom, const char *s, unsigned int len){
	size_t n;
	for(n = 0; n < bloom->nfuncs; ++n) {
		if(!(GETBIT(bloom->a, bloom->funcs[n](s, len) % bloom->asize))){
            return 0;
        }
	}
	return 1;
}
