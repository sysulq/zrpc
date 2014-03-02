#include "zrpc_reply.h"

int zrpc_sync_reply(zrpc_server_t *zrpc, char *reply)
{
    dd("server reply:%s\n", reply);
    zstr_send(zrpc->zrpc_server, reply);
}
