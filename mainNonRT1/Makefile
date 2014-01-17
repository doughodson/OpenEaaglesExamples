
include ../makedefs

PGM = mainNonRT1

OBJS = main.o

LDFLAGS += -loeSensors -loeVehicles -loeSimulation -lJSBSim 
LDFLAGS += -loeInstruments -loeDafif
LDFLAGS += -loeBasic 
LDFLAGS += -lrt -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread

CPPFLAGS += -I/usr/local/include

all: $(PGM)

edl:
	cpp configs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp configs/test2.epp >test2.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)


