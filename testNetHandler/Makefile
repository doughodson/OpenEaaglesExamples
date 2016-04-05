#
include ../makedefs

PGM = testNetHandler

OBJS = Sender.o main.o Endpoint.o Echo.o ServerTcpMultiple.o

LDFLAGS += -L../lib/linux -lxzmq -lzmq
LDFLAGS += -loebase -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
