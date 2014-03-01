CC = gcc
AR = ar

LIBNAME = libzrpc.a

TESTSRCS := test_client.c test_server.c
LIBSRCS = zrpc.c
DEPS = zrpc.h zrpc_debug.h

CFLAGS += -g -lzmq -lczmq -I. -L.

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
	cd $(BUILD)/ && $(CC) $(LIBNAME) $(CFLAGS) -I../src -o $$(notdir $$@) ../$$<
endef
$(foreach s,$(TESTSRCS),$(eval $(call TEST_action,$(s))))

test: $(TEST)

clean:
	rm -rf *.o $(LIBNAME) $(TEST) $(BUILD)
