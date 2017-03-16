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
	factory.o \
	main.o

LDFLAGS += -loe_base -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
