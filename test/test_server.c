#include <zrpc.h>

int test_handler(void *arg)
{
	zrpc_server_t *server = (zrpc_server_t *)arg;

    dd("handler.");
    zrpc_sync_reply(server, "WORLD");
}

int main()
{
    zrpc_server_t *server = zrpc_server_new();

    zrpc_service_t *service = zrpc_service_new();

    zrpc_service_register(service, test_handler);

    zrpc_server_register_service(server, service);

    zrpc_loop(server);

    dd("server reply done.");

    zrpc_server_destroy(server);

    return 0;
}

