#
include ../makedefs

PGM = tutorial06

OBJS = main.o MyComp.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/file0.epp >file0.edl   $(EPPFLAGS)
	cpp inputs/file1.epp >file1.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f ${PGM}

