#
include ../makedefs

PGM = mainfd2

OBJS =  \
	main.o \
	Pfd.o \
	SpdLines.o \
	TestPfd.o

LDFLAGS += -lpthread -loeGlut -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
