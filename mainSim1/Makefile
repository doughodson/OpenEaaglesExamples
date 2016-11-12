
include ../makedefs

PGM = mainSim1

OBJS = main.o

LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -loedis -loemodels -loesimulation
LDFLAGS += -loeotw -loedafif -loebase
LDFLAGS += -lcigicl -lJSBSim
LDFLAGS += -lrt -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM)

edl:
	cpp configs/test0.epp > test0.edl $(EPPFLAGS)
	cpp configs/test1.epp > test1.edl $(EPPFLAGS)
	cpp configs/test2.epp > test2.edl $(EPPFLAGS)
	cpp configs/test3.epp > test3.edl $(EPPFLAGS)
	cpp configs/test4.epp > test4.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
