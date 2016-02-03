#
include ../makedefs

PGM = mainLaero

OBJS =  \
	main.o \
	AdiDisplay.o \
	Factory.o \
	MapDisplay.o \
	MapPage.o \
	TestStation.o

LDFLAGS += -L../lib/linux -lxZeroMQHandlers -lzmq
LDFLAGS += -loesimulation -loedynamics -loedafif
LDFLAGS += -loesensor -loedis
LDFLAGS += -lJSBSim
LDFLAGS += -loeglut -loeinstruments -loeBasicGL -loebasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
