CC = gcc
AR = ar

LIBNAME = libzrpc.a

TESTSRCS := test_client.c test_server.c
LIBSRCS = zrpc_server.c zrpc_client.c zrpc_request.c zrpc_reply.c zrpc_service.c zrpc.pb-c.c
PROTOSRCS = zrpc.proto

DEPS = zrpc.h zrpc_pbc.h zrpc_debug.h

CFLAGS += -g -lzmq -lczmq -lprotobuf-c -I../include -I../deps/pbc

all: $(BUILD) $(LIBNAME) test

BUILD = build

$(BUILD): 
	mkdir -p $@

LIB:=
define LIB_action
TAR := $(BUILD)/$(notdir $(basename $(1)))
LIB := $(LIB) $$(TAR).o
-include $$(TAR).d
$$(TAR).o :| $(BUILD)
$$(TAR).o : src/$(1)
	$(CC) -c $(CFLAGS) -o $$@ $$<
endef
$(foreach s,$(LIBSRCS), $(eval $(call LIB_action,$(s))))

$(LIBNAME): $(LIB) $(BUILD)
	cd $(BUILD) && $(AR) -r $@ $(addprefix ../,$(LIB))

TEST:=
define TEST_action
TAR := $(BUILD)/$(notdir $(basename $(1)))
TEST := $(TEST) $$(TAR)
$$(TAR) : | $(BUILD)
$$(TAR) : $(LIBNAME)
$$(TAR) : test/$(1)
	cd $(BUILD)/ && $(CC) $(LIBNAME) $(CFLAGS) -o $$(notdir $$@) ../$$<
endef
$(foreach s,$(TESTSRCS),$(eval $(call TEST_action,$(s))))

test: $(TEST) proto

PROTO :=
define PROTO_action
TAR := $(BUILD)/$(notdir $(basename $(1)))
PROTO := $(PROTO) $$(TAR).pb
$$(TAR).pb :| $(BUILD)
$$(TAR).pb : src/$(1)
	protoc -o$$@ $$<
endef
$(foreach s,$(PROTOSRCS),$(eval $(call PROTO_action,$(s))))

proto: $(PROTO)

clean:
	rm -rf $(BUILD)
