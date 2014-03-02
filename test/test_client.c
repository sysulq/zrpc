#include <zrpc.h>

int main()
{
    zrpc_t *zrpc = zrpc_client_new();

    char *reply;
    zrpc_sync_request(zrpc, "HELLO", &reply);

    dd("server reply: %s.\n", reply);
    free(reply);

    return 0;
}
