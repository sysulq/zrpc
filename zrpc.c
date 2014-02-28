#include "zrpc.h"

int zrpc_server_init(zrpc_t *zrpc)
{
    assert(zrpc);
    zrpc->zctx = zctx_new();
    assert(zrpc->zctx);

    void *zrpc_server = zsocket_new(zrpc->zctx, ZMQ_REP);
    assert(zrpc_server);
    zsocket_bind(zrpc_server, "tcp://*:5566");

    zrpc->zrpc_server = zrpc_server;
}

int zrpc_client_init(zrpc_t *zrpc)
{
    assert(zrpc);
    zrpc->zctx = zctx_new();
    assert(zrpc->zctx);

    void *zrpc_client = zsocket_new(zrpc->zctx, ZMQ_REQ);
    assert(zrpc_client);

    zrpc->zrpc_client = zrpc_client;
}

int zrpc_exit(zrpc_t *zrpc)
{
    assert(zrpc);
    zctx_destroy(&zrpc->zctx);
}

int zrpc_poll(zrpc_t *zrpc)
{
    while(!zctx_interrupted) {
        zmq_pollitem_t items = {zrpc->zrpc_server, 0, ZMQ_POLLIN, 0};

        int rc = zmq_poll(&items, 1, -1);
        if (rc == -1)
            break;

        if (items.revents & ZMQ_POLLIN) {
            char *msg = zstr_recv(zrpc->zrpc_server);
            dd("client msg:%s", msg);
            zrpc_sync_reply(zrpc, "WORLD");
            free(msg);
        }
    }
}

int zrpc_sync_request(zrpc_t *zrpc, const char *request, char **reply)
{
    assert(zrpc);

    zsocket_connect(zrpc->zrpc_client, "tcp://localhost:5566");
    printf("client request:%s\n", request);

    zstr_send(zrpc->zrpc_client, request);

    *reply = zstr_recv(zrpc->zrpc_client);
    if (!*reply)
        return -1;
}

int zrpc_sync_reply(zrpc_t *zrpc, char *reply)
{
    dd("server reply:%s\n", reply);
    zstr_send(zrpc->zrpc_server, reply);
}

