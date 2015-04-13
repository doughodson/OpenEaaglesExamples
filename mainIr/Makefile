#
include ../makedefs

PGM = mainIr

OBJS =	Factory.o TestComputer.o TestDisplay.o TestStation.o main.o

LDFLAGS += -loeDis -loeSensors -loeDynamics -loeSimulation -loeInstruments -lJSBSim
LDFLAGS += -loeIoDevice -loeOtw -loeDafif 
LDFLAGS += -loeGlut -loeBasicGL -loeBasic -lftgl -lfreetype -lcigicl 
LDFLAGS += -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

edl:
	cpp configs/test1.epp > test1.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

