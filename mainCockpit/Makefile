#
include ../makedefs

PGM = mainCockpit

OBJS  = SimStation.o TestDisplay.o
OBJS += TestIoHandler.o
OBJS += factory.o main.o

LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -lxpanel
LDFLAGS += -loerecorder -loemodels
LDFLAGS += -loesimulation -loeinstruments -loedis
LDFLAGS += -loeiodevice -loeotw -loedafif
LDFLAGS += -loeglut -loegraphics -loebase
LDFLAGS += -lprotobuf -lJSBSim
LDFLAGS += -lftgl -lfreetype -lcigicl
LDFLAGS += -lglut -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include
LDFLAGS  += -L../lib/linux -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test1.epp >test1.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
