#
include ../makedefs

PGM = mainUbf1

#
OBJS = main.o
OBJS += SimStation.o TestDisplay.o
OBJS += TestIoHandler.o factory.o

LDFLAGS += -loe_models -lJSBSim
LDFLAGS += -lxbehaviors -lxpanel
LDFLAGS += -loe_interop_dis -loe_interop -loe_graphics -loe_gui_glut -loe_instruments -loe_simulation
LDFLAGS += -loe_iodevice -loe_otw -loe_terrain
LDFLAGS += -lJSBSim -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test00.epp > test00.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
