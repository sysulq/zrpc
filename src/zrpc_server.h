#ifndef __ZRPC_SERVER_INCLUDE__
#define __ZRPC_SERVER_INCLUDE__

#include <czmq.h>
#include "zrpc_debug.h"
#include "zrpc_service.h"

typedef struct zrpc_server zrpc_server_t;

struct zrpc_server {
    zctx_t          *zctx;
    zloop_t         *zloop;
    void            *zrpc_server;
    void            *data;

    zrpc_service_t  *service;
};

zrpc_server_t *zrpc_server_new();
int zrpc_server_exit(zrpc_server_t *zrpc);

int zrpc_register_service(zrpc_server_t *self, zrpc_service_t *service);

int zrpc_loop(zrpc_server_t *zrpc);

#endif

