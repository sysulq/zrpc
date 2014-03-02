#ifndef __ZRPC_INCLUDE__
#define __ZRPC_INCLUDE__

#include <czmq.h>
#include "zrpc_debug.h"
#include "zrpc_service.h"

typedef struct zrpc zrpc_t;

struct zrpc {
    zctx_t          *zctx;
    zloop_t         *zloop;
    void            *zrpc_server;
    void            *zrpc_client;
    void            *data;

    zrpc_service_t  *service;
};

zrpc_t *zrpc_server_new();
zrpc_t *zrpc_client_new();
int zrpc_exit(zrpc_t *zrpc);

int zrpc_loop(zrpc_t *zrpc);

int zrpc_sync_request(zrpc_t *zrpc, const char *request, char **reply);
int zrpc_sync_reply(zrpc_t *zrpc, char *reply);

#endif

