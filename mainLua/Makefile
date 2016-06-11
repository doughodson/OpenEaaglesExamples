#
include ../makedefs

PGM = mainLua

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
LDFLAGS += -loeglut -loeinstruments -loegraphics -loeotw
LDFLAGS += -loebehaviors -loeclips -loelua -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread -lcigicl
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
