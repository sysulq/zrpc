#ifndef __ZRPC_INCLUDE__
#define __ZRPC_INCLUDE__

#include "czmq.h"

typedef struct zrpc zrpc_t;

struct zrpc {
    zctx_t *zctx;
    void   *zrpc_server;
    void   *zrpc_client;
};

int zrpc_client_init(zrpc_t *zrpc);
int zrpc_server_init(zrpc_t *zrpc);
int zrpc_exit(zrpc_t *zrpc);

int zrpc_poll(zrpc_t *zrpc);

int zrpc_sync_request(zrpc_t *zrpc, const char *request, char **reply);
int zrpc_sync_reply(zrpc_t *zrpc, char *reply);

#endif

