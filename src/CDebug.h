#ifndef CDEBUG_H
#define CDEBUG_H

#ifdef CIVSIM_DBG
	#define C_DBG(a, ...) printf("MEDIAPLUGIN (%s:%d): " a "\n", \
                        __PRETTY_FUNCTION__, \
	                        __LINE__, \
	                        ##__VA_ARGS__)
#else
	#define C_DBG(a, ...)
#endif

class CDebug {
public:
    static void dbg(char * format, ...);
}

#endif //CDEBUG_H
