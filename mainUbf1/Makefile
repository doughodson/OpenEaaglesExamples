#
include ../makedefs

PGM = mainUbf1

#
OBJS = main.o
OBJS += SimStation.o TestDisplay.o
OBJS += TestIoHandler.o factory.o

LDFLAGS += -lxbehaviors -lxpanel
LDFLAGS += -loegraphics -loeglut -loeinstruments -loesimulation
LDFLAGS += -loedis -loemodels -loeiodevice -loeotw -loedafif
LDFLAGS += -lJSBSim -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test00.epp > test00.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
