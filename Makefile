CC = gcc
AR = ar

DIR = $(echo $(shell pwd))

LIBNAME = libzrpc.a

TESTSRCS := test_client.c test_server.c

CFLAGS += -g -lzmq -lczmq -I. -L.

all: $(LIBNAME) test $(BUILD)

SRC = zrpc.c
DEPS = zrpc.h zrpc_debug.h

OBJ =  zrpc.o 

BUILD = build

$(BUILD): 
	mkdir -p $@

$(LIBNAME): $(OBJ)
	$(AR) -r $@ $(OBJ)

$(OBJ): $(SRC) $(DEPS)
	$(CC) -c $(CFLAGS) $(SRC) -o $@

TEST:=
define TEST_action
TAR := $(BUILD)/$(notdir $(basename $(1)))
TEST := $(TEST) $$(TAR)
$$(TAR) : | $(BUILD)
$$(TAR) : $(LIBNAME)
$$(TAR) : test/$(1)
	cd $(BUILD)/ && $(CC) ../$(LIBNAME) $(CFLAGS) -o $$(notdir $$@) ../$$<
endef
$(foreach s,$(TESTSRCS),$(eval $(call TEST_action,$(s))))

test: $(TEST)

clean:
	rm -rf *.o $(LIBNAME) $(TEST) $(BUILD)
