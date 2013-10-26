#
include ../makedefs

PGM = testNet

OBJS = ClientSide.o testNet.o NetTester.o ServerSide.o ServerTcpMultiple.o

LDFLAGS += -loeBasic -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
