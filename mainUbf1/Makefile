#
include ../makedefs

PGM = mainUbf1

SUBDIRS = planeBehaviors

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
LDFLAGS  += -L./planeBehaviors -L$(OPENEAAGLES_LIB_DIR)

EPPFLAGS += -I.

all: subdirs $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/agentTest.epp    >agentTest.edl   $(EPPFLAGS)
	cpp inputs/simAgentTest.epp >simAgentTest.edl   $(EPPFLAGS)

subdirs:
	for subdir in $(SUBDIRS); do \
	  echo making $@ in $$subdir; \
	  (cd $$subdir && $(MAKE)) || exit 1; \
	done

clean:
	-rm -f *.o
	for subdir in $(SUBDIRS); do \
	    echo making $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done
	-rm -f $(PGM)

