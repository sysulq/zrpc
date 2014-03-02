#include "zrpc_reply.h"
#include <stdlib.h>

#define ERROR_LEN 32

Zrpc__Reply *zrpc_reply_new()
{
    Zrpc__Reply *self = (Zrpc__Reply*)malloc(sizeof(Zrpc__Reply));
    assert(self);
    self->error = (char*)malloc(ERROR_LEN);
}

int zrpc_request_exit(Zrpc__Reply *self)
{
    assert(self);
    free(self->error);
}
