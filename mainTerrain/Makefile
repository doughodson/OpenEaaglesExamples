#
include ../makedefs

PGM = mainTerrain
OBJS =  Display.o Factory.o main.o

LDFLAGS += -loesimulation -loeterrain
LDFLAGS += -loeglut -loegraphics -loebasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl  $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
