include ../makedefs

PGM = testRecorderRead

OBJS = main.o DataRecordTest.o Factory.o PrintMyData.o

LDFLAGS += -lxRecorder
LDFLAGS += -loeRecorder -loeSimulation
LDFLAGS += -loeDafif -loeBasic
LDFLAGS += -lprotobuf
LDFLAGS += -lrt -lpthread 

CPPFLAGS += -I/usr/local/include
LDFLAGS  += -L../lib/linux -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS +=  -I.

all: $(PGM) 

edl:
	cpp configs/test.epp >test.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)


