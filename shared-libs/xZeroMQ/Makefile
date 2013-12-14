#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxZeroMQHandlers.a

OBJS += \
	$(LIB)(ZeroMQContext.o) \
	$(LIB)(ZeroMQHandler.o)

all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)
	-rm -f *~

