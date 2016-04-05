
include ../makedefs

PGM = mainNonRT1

OBJS = main.o

LDFLAGS += -loemodels -loesimulation -lJSBSim
LDFLAGS += -loeinstruments -loedafif
LDFLAGS += -loebase
LDFLAGS += -lrt -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread

CPPFLAGS += -I/usr/local/include

all: $(PGM)

edl:
	cpp configs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp configs/test2.epp >test2.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
