#ifndef CDEBUG_H
#define CDEBUG_H

#include <stdio.h>

#ifdef CIVSIM_DBG
	#define C_DBG(a, ...) printf("CIVSIM: %s[%d]: " a "\n", \
                        __PRETTY_FUNCTION__, \
	                        __LINE__, \
	                        ##__VA_ARGS__)
#else
	#define C_DBG(a, ...)
#endif

class CDebug {
public:
    static void dbg(char * format, ...);
};

#endif //CDEBUG_H
