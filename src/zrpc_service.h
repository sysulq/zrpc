#ifndef __ZRPC_SERVICE_INCLUDE__
#define __ZRPC_SERVICE_INCLUDE__

typedef struct zrpc_service zrpc_service_t;

struct zrpc_service {
    const char *method;
    const void *payload;
    size_t      length;
};

#endif