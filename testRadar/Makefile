#
include ../makedefs

PGM = testRadar

OBJS =	DspRadar.o DspRwr.o TdAzPtr.o TdElevPtr.o \
	TestDisplay.o TestStation.o factory.o main.o

LDFLAGS += -loe_interop_dis -loe_interop
LDFLAGS += -loe_models -lJSBSim
LDFLAGS += -loe_simulation
LDFLAGS += -loe_gui_glut -loe_instruments -loe_graphics
LDFLAGS += -loe_iodevice -loe_terrain
LDFLAGS += -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread -lrt

EPPFLAGS += -I.

all: $(PGM)

edl:
	cpp configs/test1.epp  >test1.edl    $(EPPFLAGS)
	cpp configs/test2a.epp >test2a.edl   $(EPPFLAGS)
	cpp configs/test2b.epp >test2b.edl   $(EPPFLAGS)
	cpp configs/test2c.epp >test2c.edl   $(EPPFLAGS)
	cpp configs/test3a.epp >test3a.edl   $(EPPFLAGS)
	cpp configs/test3b.epp >test3b.edl   $(EPPFLAGS)
	cpp configs/test4a.epp >test4a.edl   $(EPPFLAGS)
	cpp configs/test4b.epp >test4b.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
