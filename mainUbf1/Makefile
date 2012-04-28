#
include ../makedefs

PGM = mainUbf1

#
OBJS = mainUbf1.o
OBJS += Hsi.o DspRadar.o DspRwr.o SimStation.o
OBJS += SpdLines.o TdAzPtr.o TdElevPtr.o TestDisplay.o
OBJS += TestIoHandler.o formFunc.o Pfd.o
#
# ubf arbiters
OBJS += ubf/DumbArbiter.o ubf/PriorityArbiter.o
# ubf action
OBJS += ubf/PlaneAction.o
# ubf agent
OBJS += ubf/PlaneAgent.o
# ubf state
OBJS += ubf/PlaneState.o
# ubf behaviors
OBJS += ubf/PlaneBarrelRoll.o
OBJS += ubf/PlaneClimb.o
OBJS += ubf/PlaneDive.o
OBJS += ubf/PlaneFire.o
OBJS += ubf/PlaneFlyStraight.o
OBJS += ubf/PlaneFollowEnemy.o
OBJS += ubf/PlaneLoop.o
OBJS += ubf/PlaneRoll.o
OBJS += ubf/PlaneSlowTurn.o
OBJS += ubf/PlaneTrim.o
OBJS += ubf/PlaneTurn.o
# ubf form func
OBJS += ubf/ubfFF.o

LDFLAGS += -loeUbf
LDFLAGS += -loeGlut -loeBasicGL -loeInstruments -loeSimulation
LDFLAGS += -loeDis -loeSensors -loeVehicles -loeIoDevice -loeOtw -loeDafif
LDFLAGS += -lJSBSim -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lcigicl
LDFLAGS += -lpthread -lrt

CPPFLAGS += -I../
LDFLAGS  += -L../lib/linux

EPPFLAGS += -I.

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/test1.epp >test1.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

