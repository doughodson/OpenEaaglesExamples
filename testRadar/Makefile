#
include ../makedefs

PGM = testRadar

OBJS =	DspRadar.o DspRwr.o TdAzPtr.o TdElevPtr.o \
	TestDisplay.o TestStation.o Factory.o testx.o

LDFLAGS += -loeDis -loeSensors -loeVehicles -loeSimulation -loeInstruments
LDFLAGS += -loeIoDevice -loeDafif -loeGlut -loeBasicGL -loeBasic -lJSBSim
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread -lrt

EPPFLAGS += -I.

all: $(PGM)

edl:
	cpp configs/test1.epp  >test1.edl    $(EPPFLAGS)
	cpp configs/test2a.epp >test2a.edl   $(EPPFLAGS)
	cpp configs/test2b.epp >test2b.edl   $(EPPFLAGS)
	cpp configs/test2c.epp >test2c.edl   $(EPPFLAGS)
	cpp configs/test3a.epp >test3a.edl   $(EPPFLAGS)
	cpp configs/test3b.epp >test3b.edl   $(EPPFLAGS)
	cpp configs/test4a.epp >test4a.edl   $(EPPFLAGS)
	cpp configs/test4b.epp >test4b.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

