#
include ../makedefs

PGM = mainUbf1

#
OBJS = mainUbf1.o
OBJS += SimStation.o TestDisplay.o
OBJS += TestIoHandler.o formFunc.o

LDFLAGS += -lPlaneBehaviors -lY1Panel
LDFLAGS += -loeBasicGL -loeGlut -loeInstruments -loeSimulation
LDFLAGS += -loeDis -loeSensors -loeVehicles -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -lJSBSim -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L../lib/linux -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/agentTest.epp    >agentTest.edl   $(EPPFLAGS)
	cpp inputs/simAgentTest.epp >simAgentTest.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

