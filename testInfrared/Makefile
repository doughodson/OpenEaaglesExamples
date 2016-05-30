#
include ../makedefs

PGM = testInfrared

OBJS =	factory.o TestComputer.o TestDisplay.o TestStation.o main.o

LDFLAGS += -loedis -loemodels -loesimulation -loeinstruments -lJSBSim
LDFLAGS += -loeiodevice -loeotw -loedafif
LDFLAGS += -loeglut -loegraphics -loebase -lftgl -lfreetype -lcigicl
LDFLAGS += -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

edl:
	cpp configs/test1.epp > test1.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
