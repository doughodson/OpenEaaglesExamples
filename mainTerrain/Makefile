#
include ../makedefs

PGM = mainTerrain
OBJS =  Display.o factory.o main.o

LDFLAGS += -loe_terrain -loe_simulation
LDFLAGS += -loe_gui_glut -loe_graphics -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl  $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
