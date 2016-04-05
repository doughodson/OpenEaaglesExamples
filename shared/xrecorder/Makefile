#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxrecorder.a

OBJS += \
	protobuf/DataRecord.pb.o \
	DataRecorder.o \
	factory.o

.PHONY: all clean

all: $(LIB)

$(LIB) : $(OBJS)
	ar rs $@ $(OBJS)

clean:
	-rm -f protobuf/*.o
	-rm -f *.o
	-rm -f $(LIB)
