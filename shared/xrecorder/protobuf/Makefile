#
include ../../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxrecorder.a

OBJS += \
	DataRecord.pb.o

.PHONY: all clean

all: $(LIB)

$(LIB) : $(OBJS)
	ar r $(LIB) $(OBJS)

clean:
	-rm -f *.o
	-rm -f $(LIB)

