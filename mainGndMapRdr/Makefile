#
include ../makedefs

PGM = mainGndMapRdr
OBJS = Display.o factory.o main.o RealBeamRadar.o TestStation.o

LDFLAGS += -loe_models -lJSBSim
LDFLAGS += -loe_terrain -loe_simulation
LDFLAGS += -loe_gui_glut -loe_graphics
LDFLAGS += -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
