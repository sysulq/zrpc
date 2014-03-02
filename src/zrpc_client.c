#include "zrpc_client.h"

zrpc_client_t *zrpc_client_new()
{
    zrpc_client_t *self = malloc(sizeof(zrpc_client_t));
    assert(self);

    self->zctx = zctx_new();
    assert(self->zctx);

    self->zclient = zsocket_new(self->zctx, ZMQ_REQ);
    assert(self->zclient);

    return self;
}

int zrpc_client_destroy(zrpc_client_t *self)
{
    assert(self);

    if (self->zctx)
        zctx_destroy(&self->zctx);

    free(self);
}
