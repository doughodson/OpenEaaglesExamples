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
    
LDFLAGS += -loe_models -loe_simulation -loe_dafif -loe_terrain -loe_base 
LDFLAGS += -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm models/*.o
	-rm -f *.o
	-rm -f $(PGM)
