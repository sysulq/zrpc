CC = gcc
AR = ar

TARGET = libzrpc.a

TEST := client server

CFLAGS += -g -lzmq -lczmq

all: $(TARGET) $(TEST)

SRC = zrpc.c
DEPS = zrpc.h zrpc_debug.h

OBJ =  zrpc.o 

$(TARGET): $(OBJ)
	$(AR) -r $@ $(OBJ)

$(OBJ): $(SRC) $(DEPS)
	$(CC) -c $(CFLAGS) $(SRC) -o $@

client: test_client.c
	$(CC) $< $(TARGET) $(CFLAGS) -o $@

server: test_server.c
	$(CC) $< $(TARGET) $(CFLAGS) -o $@

clean:
	rm -f *.o $(TARGET) $(TEST)
