#include "zrpc_request.h"

int zrpc_sync_request(zrpc_client_t *zrpc, const char *request, char **reply)
{
    assert(zrpc);

    zsocket_connect(zrpc->zclient, "tcp://localhost:5566");
    dd("client request:%s\n", request);

    zstr_send(zrpc->zclient, request);

    *reply = zstr_recv(zrpc->zclient);
    if (!*reply)
        return ZRPC_ERR;
}