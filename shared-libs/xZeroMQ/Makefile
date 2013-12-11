#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxZeroMQ.a

OBJS += \
	$(LIB)(Context.o) \
	$(LIB)(Socket.o)

all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)
	-rm -f *~

