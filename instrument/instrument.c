/*#include <stdio.h>

#define DUMP(func, call) printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)

void __cyg_profile_func_enter( void *, void * ) 
	__attribute__ ((no_instrument_function));

void __cyg_profile_func_exit( void *, void * )
	__attribute__ ((no_instrument_function));
	
void __cyg_profile_func_enter(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
}
void __cyg_profile_func_exit(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
} */

#include <stdio.h>
#include <malloc.h>
#include <execinfo.h>
#define debug_print(fmt, args...) do { \
            fprintf(stderr, fmt, ##args); \
        }while(0)


void __cyg_profile_func_exit(void* callee, void* callsite) __attribute__((no_instrument_function));
void __cyg_profile_func_enter(void* callee, void* callsite) __attribute__((no_instrument_function));


void __cyg_profile_func_enter(void* callee, void* callsite) {
    char **pcallee = backtrace_symbols(&callee, 1);
    char **pcallsite = backtrace_symbols(&callsite, 1);
    printf("=== Entering: %s, called by: %s\n", *pcallee, *pcallsite);
    free(pcallee);
    free(pcallsite);
}


void __cyg_profile_func_exit(void* callee, void* callsite) {
    char **pcallee = backtrace_symbols(&callee, 1);
    char **pcallsite = backtrace_symbols(&callsite, 1);
    printf("=== Leaving: %s, called by: %s\n", *pcallee, *pcallsite);
    free(pcallee);
    free(pcallsite);
}
