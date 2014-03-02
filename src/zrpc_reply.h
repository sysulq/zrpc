#ifndef __ZRPC_REPLY_INCLUDE__
#define __ZRPC_REPLY_INCLUDE__

#include <czmq.h>
#include "zrpc_debug.h"
#include "zrpc_server.h"

int zrpc_sync_reply(zrpc_server_t *zrpc, char *reply);

#endif

