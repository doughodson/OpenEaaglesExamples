#
include ../makedefs

PGM = mainGndMapRdr
OBJS = Display.o factory.o main.o RealBeamRadar.o TestStation.o

LDFLAGS += -loemodels -lJSBSim
LDFLAGS += -loeterrain -loesimulation
LDFLAGS += -loeglut -loegraphics
LDFLAGS += -loedafif -loebase
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
