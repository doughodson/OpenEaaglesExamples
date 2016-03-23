#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxzmq.a

OBJS += \
	factory.o \
	ZeroMQContext.o \
	ZeroMQHandler.o

.PHONY: all clean

all: $(LIB)

$(LIB) : $(OBJS)
	ar r $(LIB) $(OBJS)

clean:
	-rm -f *.o
	-rm -f $(LIB)
	-rm -f *~

