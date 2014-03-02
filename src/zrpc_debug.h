#ifndef __ZRPC_DEBUG__
#define __ZRPC_DEBUG__

#define DDEBUG 1

#define ZRPC_OK 0
#define ZRPC_ERR -1

#if defined(DDEBUG) && (DDEBUG)

#define dd(...) fprintf(stderr, "zrpc *** %s: ", __func__); \
            fprintf(stderr, __VA_ARGS__); \
            fprintf(stderr, " at %s line %d.\n", __FILE__, __LINE__)

#else

static inline void dd(const char *fmt, ...) {
}

#endif

#endif
