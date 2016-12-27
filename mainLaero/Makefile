#
include ../makedefs

PGM = mainLaero

OBJS =  \
	main.o \
	AdiDisplay.o \
	factory.o \
	MapDisplay.o \
	MapPage.o \
	TestStation.o

LDFLAGS += -loedis -loeinterop
LDFLAGS += -loemodels -lJSBSim
LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -loesimulation -loemodels -loedafif
LDFLAGS += -loeglut -loeinstruments -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
