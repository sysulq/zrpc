#ifndef __ZRPC_SERVICE_INCLUDE__
#define __ZRPC_SERVICE_INCLUDE__

#include <stdlib.h>

typedef struct zrpc_service zrpc_service_t;

typedef int (zrpc_service_handler_fn)(void *arg);

struct zrpc_service {
    zrpc_service_handler_fn *handler;
    void                    *arg;  
};

zrpc_service_t *zrpc_service_new(zrpc_service_handler_fn *handler);

#endif