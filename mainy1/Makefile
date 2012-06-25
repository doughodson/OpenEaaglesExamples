#
include ../makedefs

PGM = mainy1

OBJS  = Hsi.o DspRadar.o DspRwr.o SimStation.o
OBJS += SpdLines.o TdAzPtr.o TdElevPtr.o TestDisplay.o
OBJS += TestIoHandler.o
OBJS += formFunc.o Pfd.o testy.o

LDFLAGS += -loeRecorder -loeSensors -loeVehicles
LDFLAGS += -loeSimulation -loeInstruments -loeDis
LDFLAGS += -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lprotobuf -lJSBSim
LDFLAGS += -lftgl -lfreetype -lcigicl 
LDFLAGS += -lglut -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I/usr/local/include

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp inputs/recordTest.epp >recordTest.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

