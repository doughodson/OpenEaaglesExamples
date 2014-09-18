
include ../makedefs

PGM = mainSim2

OBJS = main.o

LDFLAGS += -L../lib/linux -lxZeroMQHandlers -lzmq
LDFLAGS += -loeDis -loeSensors -loeDynamics -loeSimulation
LDFLAGS += -loeOtw -loeDafif -loeBasic
LDFLAGS += -lcigicl -lJSBSim 
LDFLAGS += -lrt -lpthread 

CPPFLAGS += -I/usr/local/include

all: $(PGM) 

edl:
	cpp configs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp configs/test2.epp >test2.edl   $(EPPFLAGS)
	cpp configs/test3.epp >test3.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)


