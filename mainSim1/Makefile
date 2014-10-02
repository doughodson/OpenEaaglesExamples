include ../makedefs

PGM = mainSim1 

OBJS = main.o 

LDFLAGS += -L../lib/linux -lxZeroMQHandlers -lzmq
LDFLAGS += -loeDis -loeSensors -loeDynamics -loeSimulation
LDFLAGS += -loeOtw -loeDafif -loeBasic
LDFLAGS += -lcigicl -lJSBSim 
LDFLAGS += -lrt -lpthread 

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM) 

edl:
	cpp configs/test00.epp >test00.edl $(EPPFLAGS)
	cpp configs/test01.epp >test01.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)


