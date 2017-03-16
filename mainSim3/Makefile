
include ../makedefs

PGM = mainSim3

OBJS = \
	Display.o \
	MapPage.o \
	Station.o \
	main.o

LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -loe_interop_dis -loe_interop -loe_models -loe_simulation -lJSBSim
LDFLAGS += -loe_instruments -loe_iodevice -loe_otw -loe_terrain
LDFLAGS += -loe_gui_glut -loe_graphics -loe_base -lrt -lcigicl
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
