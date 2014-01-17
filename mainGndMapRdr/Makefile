#
include ../makedefs

PGM = mainGndMapRdr
OBJS = Display.o Factory.o main.o RealBeamRadar.o Station.o

LDFLAGS += -loeSimulation -loeSensors -loeTerrain
LDFLAGS += -loeGlut -loeBasicGL
LDFLAGS += -loeDafif -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

