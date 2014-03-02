#ifndef __ZRPC_REQUEST_INCLUDE__
#define __ZRPC_REQUEST_INCLUDE__

#include "zrpc.pb-c.h"

Zrpc__Request *zrpc_request_new();

int zrpc_request_exit(Zrpc__Request *self);

#endif