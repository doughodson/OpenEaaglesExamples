#
include ../makedefs

PGM = testTables
OBJS = main.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp inputs/test2.epp >test2.edl   $(EPPFLAGS)
	cpp inputs/test3.epp >test3.edl   $(EPPFLAGS)
	cpp inputs/test3a.epp >test3a.edl   $(EPPFLAGS)
	cpp inputs/test4.epp >test4.edl   $(EPPFLAGS)
	cpp inputs/test4_24.epp >test4_24.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
