#
include ../makedefs

PGM = testDafif
OBJS =  AirportTests.o NavaidTests.o WaypointTests.o testDafif.o

LDFLAGS += -loedafif -loebase 

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
