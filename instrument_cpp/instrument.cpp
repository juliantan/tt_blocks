#include <stdio.h>
#include <malloc.h>


#define debug_print(fmt, args...) do { \
            fprintf(stderr, fmt, ##args); \
        }while(0)

extern "C" {
    void __cyg_profile_func_exit(void* callee, void* callsite) __attribute__((no_instrument_function));
    void __cyg_profile_func_enter(void* callee, void* callsite) __attribute__((no_instrument_function));
}

extern "C" {
    void print_func(int is_enter, void* callee, void* callsite) __attribute__((no_instrument_function));
    int is_std_namespace(char *symbol) __attribute__((no_instrument_function));
}

#include <cxxabi.h>
#include <string.h>
int is_std_namespace(char *symbol)
{
    char buff[256] = {0};
    strcpy(buff, symbol);
    char *pb = buff;
    char *ps = NULL;
    while (*pb && *pb != '(') {
        pb++;
    }
    if (*pb == '(') {
        pb++;
        ps = pb;
        while (*pb && *pb != '+') {
            pb++;
        }
        *pb = '\0';
    }
    int status;
    char *realname = abi::__cxa_demangle(ps, 0, 0, &status);
    int ret = 0;
    if (realname)
    {   
        char *pstd = strstr(realname, "std::"); 
        if (pstd && pstd < strstr(realname, "("))
        {
          ret = 1;
        }
        free(realname);
    }
    return ret;
}

#include <execinfo.h>
void print_func(int is_enter, void *callee, void *callsite) {
    char **pcallee = backtrace_symbols(&callee, 1);
    char **pcallsite = backtrace_symbols(&callsite, 1);

    //: tanjl: not print for std::
    if (is_std_namespace(*pcallee) || is_std_namespace(*pcallsite)) {
        return;
    }

    if (is_enter) {
        debug_print("=== Entering: ");
    } else {
        debug_print("=== Leaving: ");
    }
    printf("%s, called by: %s\n", *pcallee, *pcallsite);
    free(pcallee);
    free(pcallsite);
}

void __cyg_profile_func_enter(void* callee, void* callsite) {
    print_func(1, callee, callsite);
}


void __cyg_profile_func_exit(void* callee, void* callsite) {
    print_func(0, callee, callsite);
}


/* for Android
#include <cxxabi.h>
void dumpAddr(void* _addr)
{
        const void* addr = _addr;
        const char* symbol = "";
        Dl_info info;
        if (dladdr(addr, &info) && info.dli_sname) {
            symbol = info.dli_sname;
			//: tanjl: not print for std::
			int status;
			char *realname = abi::__cxa_demangle(symbol, 0, 0, &status);
			if (realname)
			{
				char *pstd = strstr(realname, "std::");
				if (!(pstd && pstd < strstr(realname, "(")))
				{
				  printf("addr: %p, symbol: %s\n", addr, realname);
				}
				free(realname);
			}
        }
}
*/
