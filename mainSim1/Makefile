include ../makedefs

PGM = mainSim1 

OBJS = main.o 

LDFLAGS += -loeDis -loeSensors -loeVehicles -loeSimulation -lJSBSim 
LDFLAGS += -loeInstruments -loeOtw -loeDafif
LDFLAGS += -loeBasicGL -loeBasic -lrt -lcigicl
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread 

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM) 

edl:
	cpp inputs/test.epp >test.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)


