#include "zrpc.h"

int zrpc_server_init(zrpc_t *zrpc, zrpc_handler_fn *handler)
{
    assert(zrpc);
    memset(zrpc, 0, sizeof(zrpc_t));

    zrpc->zctx = zctx_new();
    assert(zrpc->zctx);
    zrpc->zloop = zloop_new();
    assert(zrpc->zloop);

    void *zrpc_server = zsocket_new(zrpc->zctx, ZMQ_REP);
    assert(zrpc_server);
    zsocket_bind(zrpc_server, "tcp://*:5566");

    zrpc->zrpc_server = zrpc_server;
    zrpc->handler = handler;
}

int zrpc_client_init(zrpc_t *zrpc)
{
    assert(zrpc);
    memset(zrpc, 0, sizeof(zrpc_t));

    zrpc->zctx = zctx_new();
    assert(zrpc->zctx);

    void *zrpc_client = zsocket_new(zrpc->zctx, ZMQ_REQ);
    assert(zrpc_client);

    zrpc->zrpc_client = zrpc_client;
}

int zrpc_exit(zrpc_t *zrpc)
{
    assert(zrpc);
    if (zrpc->zloop)
        zloop_destroy(&zrpc->zloop);

    if (zrpc->zctx)
        zctx_destroy(&zrpc->zctx);
}

static int loop_handler(zloop_t *loop, zmq_pollitem_t *item, void *arg)
{
    zrpc_t *zrpc = (zrpc_t *)arg;
    zrpc->data = zstr_recv(zrpc->zrpc_server);

    if (!zrpc->data)
        return ZRPC_ERR;

    if (zrpc->handler) {
        zrpc->handler(zrpc);
        return ZRPC_OK;
    }

    dd("no registered handler");
    return ZRPC_ERR;
}

int zrpc_loop(zrpc_t *zrpc)
{
    assert(zrpc);

    zmq_pollitem_t poller = {zrpc->zrpc_server, 0, ZMQ_POLLIN, 0};
    zloop_poller(zrpc->zloop, &poller, loop_handler, zrpc);
    zloop_start(zrpc->zloop);

    zrpc_exit(zrpc);
}

int zrpc_sync_request(zrpc_t *zrpc, const char *request, char **reply)
{
    assert(zrpc);

    zsocket_connect(zrpc->zrpc_client, "tcp://localhost:5566");
    dd("client request:%s\n", request);

    zstr_send(zrpc->zrpc_client, request);

    *reply = zstr_recv(zrpc->zrpc_client);
    if (!*reply)
        return ZRPC_ERR;
}

int zrpc_sync_reply(zrpc_t *zrpc, char *reply)
{
    dd("server reply:%s\n", reply);
    zstr_send(zrpc->zrpc_server, reply);
}
