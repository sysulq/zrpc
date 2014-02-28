#include "zrpc.h"

int main()
{
    zrpc_t zrpc;
    zrpc_server_init(&zrpc);

    zrpc_poll(&zrpc);

    printf("server reply done.");

    return 0;
}

