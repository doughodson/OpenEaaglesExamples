
include ../makedefs

PGM = mainSim4

OBJS = \
	Display.o \
	MapPage.o \
	Station.o \
	main.o

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
	cpp inputs/test.epp >test.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

