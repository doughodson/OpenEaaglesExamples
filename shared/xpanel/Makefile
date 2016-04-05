#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxpanel.a

OBJS += \
	DspRadar.o \
	DspRwr.o \
	factory.o \
	Hsi.o \
	Pfd.o \
	SpdLines.o \
	TdAzPtr.o \
	TdElevPtr.o

.PHONY: all clean

all: $(LIB)

$(LIB) : $(OBJS)
	ar rs $@ $(OBJS)

clean:
	-rm -f *.o
	-rm -f $(LIB)
