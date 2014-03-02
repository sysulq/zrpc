#ifndef __ZRPC_CLIENT_INCLUDE__
#define __ZRPC_CLIENT_INCLUDE__

#include <czmq.h>
#include "zrpc_debug.h"

typedef struct zrpc_client zrpc_client_t;

struct zrpc_client {
    zctx_t          *zctx;
    void            *zclient;
};

zrpc_client_t *zrpc_client_new();
int zrpc_client_exit(zrpc_client_t *zrpc);

#endif

