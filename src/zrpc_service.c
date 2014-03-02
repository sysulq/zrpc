#include "zrpc_debug.h"
#include "zrpc_service.h"
#include <czmq.h>

zrpc_service_t *zrpc_service_new(zrpc_service_handler_fn *handler)
{
    zrpc_service_t *self = malloc(sizeof(zrpc_service_t));
    assert(self);
    self->handler = handler;
    return self;
}

int zrpc_service_register(zrpc_service_t *self, zrpc_service_handler_fn *handler)
{
    assert(self && handler);
    self->handler = handler;
}

int zrpc_service_handler(zrpc_service_t *self)
{
    assert(self);

    if (self->handler) {
        self->handler(self->args);
        return ZRPC_OK;
    }

    dd("No server handler found.");
}
