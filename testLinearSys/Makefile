#
include ../makedefs

PGM = testLinearSys
OBJS = main.o

LDFLAGS += -loe_linearsystem -loe_base

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
