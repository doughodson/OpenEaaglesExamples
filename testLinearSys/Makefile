#
include ../makedefs

PGM = testLinearSys
OBJS = main.o

LDFLAGS += -loeLinearSys -loeBasic 

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
