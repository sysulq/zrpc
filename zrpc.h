#ifndef __ZRPC_INCLUDE__
#define __ZRPC_INCLUDE__

#include "czmq.h"
#include "zrpc_debug.h"

#define ZRPC_OK 0
#define ZRPC_ERR -1

typedef struct zrpc zrpc_t;

typedef int (zrpc_handler_fn) (zrpc_t *zrpc);

struct zrpc {
    zctx_t          *zctx;
    zloop_t         *zloop;
    void            *zrpc_server;
    void            *zrpc_client;
    zrpc_handler_fn *handler;
    void            *data;
};

int zrpc_server_init(zrpc_t *zrpc, zrpc_handler_fn *handler);
int zrpc_client_init(zrpc_t *zrpc);
int zrpc_exit(zrpc_t *zrpc);

int zrpc_loop(zrpc_t *zrpc);

int zrpc_sync_request(zrpc_t *zrpc, const char *request, char **reply);
int zrpc_sync_reply(zrpc_t *zrpc, char *reply);

#endif

