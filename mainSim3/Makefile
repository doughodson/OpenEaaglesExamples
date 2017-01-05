
include ../makedefs

PGM = mainSim3

OBJS = \
	Display.o \
	MapPage.o \
	Station.o \
	main.o

LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -loedis -loeinterop -loemodels -loesimulation -lJSBSim
LDFLAGS += -loeinstruments -loeiodevice -loeotw -loedafif -loeterrain
LDFLAGS += -loeglut -loegraphics -loebase -lrt -lcigicl
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
