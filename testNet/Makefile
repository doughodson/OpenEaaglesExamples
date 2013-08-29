#
include ../makedefs

PGM = testNet

OBJS = ClientSide.o testNet.o NetTester.o ServerSide.o ServerTcpMulti.o

LDFLAGS += -loeBasic -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/clientBc.epp >clientBc.edl $(EPPFLAGS)
	cpp inputs/clientMc.epp >clientMc.edl $(EPPFLAGS)
	cpp inputs/clientTcp.epp >clientTcp.edl $(EPPFLAGS)
	cpp inputs/clientUdp.epp >clientUdp.edl $(EPPFLAGS)
	cpp inputs/serverBc.epp >serverBc.edl $(EPPFLAGS)
	cpp inputs/serverMc.epp >serverMc.edl $(EPPFLAGS)
	cpp inputs/serverTcp.epp >serverTcp.edl $(EPPFLAGS)
	cpp inputs/serverTcpMulti.epp >serverTcpMulti.edl $(EPPFLAGS)
	cpp inputs/serverUdp.epp >serverUdp.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
