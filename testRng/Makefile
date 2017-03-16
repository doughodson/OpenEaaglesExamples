#
include ../makedefs

PGM = testRng
OBJS =  main.o

LDFLAGS += -loe_base

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
