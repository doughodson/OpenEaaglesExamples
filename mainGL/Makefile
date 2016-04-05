#
include ../makedefs

PGM = mainGL

OBJS = main.o

LDFLAGS += -loeglut -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/test.epp >test.edl   $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
