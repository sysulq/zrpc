#include <zrpc.h>

int test_handler(void *arg)
{
	zrpc_t *zrpc = (zrpc_t *)arg;

    dd("handler.");
    zrpc_sync_reply(zrpc, "WORLD");
}

int main()
{
    zrpc_t *zrpc = zrpc_server_new();

    zrpc->service = zrpc_service_new(test_handler);

    zrpc_loop(zrpc);

    dd("server reply done.");

    return 0;
}

