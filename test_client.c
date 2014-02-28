#include "zrpc.h"

int main()
{
    zrpc_t zrpc;
    zrpc_client_init(&zrpc);

    char reply[1];
    zrpc_sync_request(&zrpc, "HELLO", (char**)&reply);

    printf("server reply: %s.\n", (char*)reply);

    return 0;
}