#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libMyRecorder.a

OBJS += \
	$(LIB)(DataRecorder.o) \
	$(LIB)(DataRecord.pb.o) \
	$(LIB)(formFunc.o)


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

