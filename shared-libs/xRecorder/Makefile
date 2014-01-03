#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxRecorder.a

OBJS += \
	$(LIB)(DataRecorder.o) \
	$(LIB)(DataRecord.pb.o) \
	$(LIB)(Factory.o)


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

