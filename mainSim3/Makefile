
include ../makedefs

PGM = mainSim3 

OBJS = \
	InstrumentPanel.o \
	SimStation.o \
	SimIoHandler.o \
	formFunc.o \
	SimPlayer.o \
	mainSim3.o

LDFLAGS += -L../lib/linux -lxZeroMQHandlers
LDFLAGS += -loeDis -loeSensors -loeVehicles -loeSimulation -lJSBSim 
LDFLAGS += -loeInstruments -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -loeGlut -loeBasicGL -loeBasic -lrt -lcigicl 
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread 

CPPFLAGS += -I/usr/local/include 

EPPFLAGS +=  -I.

all: $(PGM) 

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

edl:
	cpp configs/test0.epp >test0.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

