
include ../makedefs

PGM = mainSim4

OBJS = \
	Display.o \
	MapPage.o \
	Station.o \
	main.o

LDFLAGS += -L../lib/linux -lxzmq -lzmq
LDFLAGS += -loedis -loemodels -loesimulation -lJSBSim 
LDFLAGS += -loeinstruments -loeiodevice -loeotw -loedafif
LDFLAGS += -loeglut -loegraphics -loebase -lrt -lcigicl 
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread 

CPPFLAGS += -I/usr/local/include 

EPPFLAGS +=  -I.

all: $(PGM) 

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

