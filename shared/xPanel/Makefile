#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxPanel.a

OBJS += \
	$(LIB)(DspRadar.o) \
	$(LIB)(DspRwr.o) \
	$(LIB)(Factory.o) \
	$(LIB)(Hsi.o) \
	$(LIB)(Pfd.o) \
	$(LIB)(SpdLines.o) \
	$(LIB)(TdAzPtr.o) \
	$(LIB)(TdElevPtr.o)


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

