#include "zrpc_server.h"

zrpc_server_t *zrpc_server_new()
{
    zrpc_server_t *zrpc = malloc(sizeof(zrpc_server_t));
    assert(zrpc);

    zrpc->zctx = zctx_new();
    assert(zrpc->zctx);
    zrpc->zloop = zloop_new();
    assert(zrpc->zloop);

    void *zrpc_server = zsocket_new(zrpc->zctx, ZMQ_REP);
    assert(zrpc_server);
    zsocket_bind(zrpc_server, "tcp://*:5566");

    zrpc->zrpc_server = zrpc_server;

    return zrpc;
}

int zrpc_server_destroy(zrpc_server_t *zrpc)
{
    assert(zrpc);
    if (zrpc->zloop)
        zloop_destroy(&zrpc->zloop);

    if (zrpc->zctx)
        zctx_destroy(&zrpc->zctx);

    free(zrpc);
}

int zrpc_server_register_service(zrpc_server_t *self, zrpc_service_t *service)
{
    assert(self && service);
    self->service = service;
    service->arg = (void*)self;
}


static int loop_handler(zloop_t *loop, zmq_pollitem_t *item, void *arg)
{
    zrpc_server_t *zrpc = (zrpc_server_t *)arg;
    zrpc->data = zstr_recv(zrpc->zrpc_server);

    if (!zrpc->data)
        return ZRPC_ERR;

    if (zrpc->service) {
        zrpc_service_handler(zrpc->service);
        return ZRPC_OK;
    }

    dd("no registered handler");
    return ZRPC_ERR;
}

int zrpc_loop(zrpc_server_t *zrpc)
{
    assert(zrpc);

    zmq_pollitem_t poller = {zrpc->zrpc_server, 0, ZMQ_POLLIN, 0};
    zloop_poller(zrpc->zloop, &poller, loop_handler, zrpc);
    zloop_start(zrpc->zloop);
}
