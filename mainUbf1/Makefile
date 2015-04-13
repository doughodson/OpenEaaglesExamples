#
include ../makedefs

PGM = mainUbf1

#
OBJS = main.o
OBJS += SimStation.o TestDisplay.o
OBJS += TestIoHandler.o Factory.o

LDFLAGS += -lxBehaviors -lxPanel
LDFLAGS += -loeBasicGL -loeGlut -loeInstruments -loeSimulation
LDFLAGS += -loeDis -loeSensors -loeDynamics -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -lJSBSim -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L../lib/linux -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test00.epp > test00.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

