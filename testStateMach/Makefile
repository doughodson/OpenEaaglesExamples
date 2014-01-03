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

clean:
	-rm -f *.o
	-rm -f $(PGM)
