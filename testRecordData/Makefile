#
include ../makedefs

PGM = testRecordData

OBJS  = SimStation.o TestDisplay.o
OBJS += TestIoHandler.o
OBJS += factory.o main.o

LDFLAGS += -lxrecorder -lxpanel
LDFLAGS += -loerecorder -loemodels
LDFLAGS += -loesimulation -loeinstruments -loedis
LDFLAGS += -loeiodevice -loeotw -loedafif
LDFLAGS += -loeglut -loegraphics -loebase
LDFLAGS += -lprotobuf -lJSBSim
LDFLAGS += -lftgl -lfreetype -lcigicl
LDFLAGS += -lglut -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
