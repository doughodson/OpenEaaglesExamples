#
include ../makedefs

PGM = testRecordData

OBJS  = SimStation.o TestDisplay.o
OBJS += TestIoHandler.o
OBJS += factory.o main.o

LDFLAGS += -loe_interop_dis -loe_interop
LDFLAGS += -loe_models
LDFLAGS += -lxrecorder -lxpanel
LDFLAGS += -loe_recorder -loe_terrain
LDFLAGS += -loe_simulation -loe_instruments
LDFLAGS += -loe_iodevice -loe_otw
LDFLAGS += -loe_gui_glut -loe_graphics -loe_base
LDFLAGS += -lprotobuf -lJSBSim
LDFLAGS += -lftgl -lfreetype -lcigicl
LDFLAGS += -lglut -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
