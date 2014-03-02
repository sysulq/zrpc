#ifndef __ZRPC_REQUEST_INCLUDE__
#define __ZRPC_REQUEST_INCLUDE__

#include <czmq.h>
#include "zrpc_debug.h"
#include "zrpc_client.h"

int zrpc_sync_request(zrpc_client_t *zrpc, const char *request, char **reply);

#endif

