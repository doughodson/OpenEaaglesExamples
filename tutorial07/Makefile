#
include ../makedefs

PGM = tutorial07

OBJS = main.o Worm.o 

LDFLAGS += -loeGlut -loeBasicGL -loeBasic 
LDFLAGS += -lpthread -lftgl -lfreetype -lglut -lGLU -lGL -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/file0.epp >file0.edl   $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f ${PGM}

