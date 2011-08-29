#
include ../makedefs

PGM = mainGndMapRdr
OBJS = Display.o formFunc.o main.o RealBeamRadar.o Station.o

LDFLAGS += -lpthread -loeSimulation -loeSensors -loeTerrain
LDFLAGS += -loeGlut -loeBasicGL
LDFLAGS += -loeDafif -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

