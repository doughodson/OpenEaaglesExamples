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

LDFLAGS += -loe_gui_glut -loe_instruments -loe_graphics -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
