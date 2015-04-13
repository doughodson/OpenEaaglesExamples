#
include ../makedefs

PGM = testTimer

OBJS = main.o Tester.o 

LDFLAGS += -loeBasic 
LDFLAGS += -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test01.epp >test01.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f ${PGM}

