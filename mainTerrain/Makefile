#
include ../makedefs

PGM = mainTerrain
OBJS =  Display.o formFunc.o main.o

LDFLAGS += -lpthread -loeSimulation -loeTerrain
LDFLAGS += -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test.epp >test.edl  $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
