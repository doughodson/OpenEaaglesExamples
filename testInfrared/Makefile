#
include ../makedefs

PGM = testInfrared

OBJS =	factory.o TestComputer.o TestDisplay.o TestStation.o main.o

LDFLAGS += -loe_interop_dis -loe_interop
LDFLAGS += -loe_models -loe_simulation -loe_instruments -lJSBSim
LDFLAGS += -loe_iodevice -loe_otw -loe_terrain
LDFLAGS += -loe_gui_glut -loe_graphics -loe_base -lftgl -lfreetype -lcigicl
LDFLAGS += -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

edl:
	cpp configs/test1.epp > test1.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
