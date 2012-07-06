#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libY1Panel.a

OBJS += \
	$(LIB)(DspRadar.o) \
	$(LIB)(DspRwr.o) \
	$(LIB)(formFunc.o) \
	$(LIB)(Hsi.o) \
	$(LIB)(Pfd.o) \
	$(LIB)(SpdLines.o) \
	$(LIB)(TdAzPtr.o) \
	$(LIB)(TdElevPtr.o)


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

