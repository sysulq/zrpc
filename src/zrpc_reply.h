#ifndef __ZRPC_REPLY_INCLUDE__
#define __ZRPC_REPLY_INCLUDE__

#include "zrpc.pb-c.h"

Zrpc__Reply *zrpc_reply_new();

int zrpc_request_exit(Zrpc__Reply *self);

#endif