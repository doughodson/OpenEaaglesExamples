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

LDFLAGS += -L../lib/linux -lxzmq -lzmq
LDFLAGS += -loesimulation -loemodels -loedafif
LDFLAGS += -loedis
LDFLAGS += -lJSBSim
LDFLAGS += -loeglut -loeinstruments -loegraphics -loebasic
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
