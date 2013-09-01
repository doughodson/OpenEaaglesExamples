#
include ../makedefs

PGM = tutorial04

OBJS = main.o Random.o Exp.o Uniform.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/file0.epp >file0.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f ${PGM}

