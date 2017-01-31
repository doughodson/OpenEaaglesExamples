#
include ../makedefs

PGM = testDafif

OBJS =  \
	models/NavRadios.o \
	models/WorldModel.o \
    AirportTests.o \
    NavaidTests.o \
    WaypointTests.o \
    testDafif.o
    
LDFLAGS += -loemodels -loesimulation -loedafif -loeterrain -loebase 
LDFLAGS += -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
