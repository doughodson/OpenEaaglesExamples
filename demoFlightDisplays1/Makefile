#
include ../makedefs

PGM = demoFlightDisplays1

OBJS =  \
	CrsPntr.o \
	Hsi.o \
	main.o \
	Pfd.o \
	RdrAlt.o \
	SituationalDisplay.o \
	SpdLines.o \
	TerrainFollower.o \
	TestPfd.o \
	TestSD.o

LDFLAGS += -loeGlut -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
