#include <zrpc.h>

int test_handler(zrpc_t *zrpc)
{
    dd("handler.");
    zrpc_sync_reply(zrpc, "WORLD");
}

int main()
{
    zrpc_t zrpc;
    zrpc_server_init(&zrpc, test_handler);

    zrpc_loop(&zrpc);

    dd("server reply done.");

    return 0;
}

