#
include ../makedefs

PGM = mainLaero

OBJS =  \
	main.o \
	AdiDisplay.o \
	formFunc.o \
	MapDisplay.o \
	MapPage.o \
	TestStation.o	

LDFLAGS += -loeSimulation -loeVehicles -loeDafif
LDFLAGS += -loeSensors -loeDis
LDFLAGS += -lJSBSim
LDFLAGS += -loeGlut -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
