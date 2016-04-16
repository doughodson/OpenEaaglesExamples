include ../makedefs

PGM = testRecorderRead

OBJS = main.o DataRecordTest.o factory.o PrintMyData.o

LDFLAGS += -lxrecorder
LDFLAGS += -loerecorder -loesimulation
LDFLAGS += -loedafif -loebase
LDFLAGS += -lprotobuf
LDFLAGS += -lrt -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)
