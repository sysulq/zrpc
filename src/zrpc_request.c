#include "zrpc_request.h"
#include <stdlib.h>

#define SERVICE_LEN 10
#define METHOD_LEN 10

Zrpc__Request *zrpc_request_new()
{
    Zrpc__Request *self = (Zrpc__Request*)malloc(sizeof(Zrpc__Request));
    assert(self);
    self->method = (char*)malloc(METHOD_LEN);
}

int zrpc_request_exit(Zrpc__Request *self)
{
    assert(self);
    free(self->method);
}
