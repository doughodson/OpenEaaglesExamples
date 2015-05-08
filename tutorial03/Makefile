#
include ../makedefs

PGM = tutorial03

OBJS = main.o Random.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/file0.epp >file0.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f ${PGM}

