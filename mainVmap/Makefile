#
include ../makedefs

PGM = mainvmap

OBJS = main.o 

LDFLAGS += -loeMaps -loeInstruments -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXmu -lXi
LDFLAGS += -lrt -lpthread

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl   $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

