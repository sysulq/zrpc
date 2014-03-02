#include "zrpc.h"

int main()
{
    zrpc_client_t *client = zrpc_client_new();

    char *reply;
    zrpc_sync_request(client, "HELLO", &reply);

    dd("server reply: %s.\n", reply);
    free(reply);

    return 0;
}
