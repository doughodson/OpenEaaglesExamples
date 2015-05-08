#
include ../makedefs

PGM = testStateMach

OBJS = \
	TestStateMachine01.o \
	TestStateMachine02.o \
	TestStateMachine03.o \
	TestStateMachine04A.o \
	TestStateMachine04B.o \
	TestStateMachine04C.o \
	TestStateMachine04.o \
	Factory.o \
	main.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp inputs/test2.epp >test2.edl   $(EPPFLAGS)
	cpp inputs/test3.epp >test3.edl   $(EPPFLAGS)
	cpp inputs/test4.epp >test4.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
