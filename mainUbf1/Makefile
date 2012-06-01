#
include ../makedefs

PGM = mainUbf1

#
OBJS = mainUbf1.o
OBJS += Hsi.o DspRadar.o DspRwr.o SimStation.o
OBJS += SpdLines.o TdAzPtr.o TdElevPtr.o TestDisplay.o
OBJS += TestIoHandler.o formFunc.o Pfd.o

LDFLAGS += -loePlaneBehaviors
LDFLAGS += -loeBasicGL -loeGlut -loeInstruments -loeSimulation
LDFLAGS += -loeDis -loeSensors -loeVehicles -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -lJSBSim -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L../planeBehaviors -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/agentTest.epp    >test1.edl   $(EPPFLAGS)
#	cpp inputs/simAgentTest.epp >test1.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

