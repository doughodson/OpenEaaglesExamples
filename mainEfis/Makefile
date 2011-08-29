#
include ../makedefs

PGM = mainEfis

OBJS = TestElectronic.o TestMechanical.o main.o 

LDFLAGS += -lpthread -loeGlut -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl   $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
