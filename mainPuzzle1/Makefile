#
include ../makedefs

PGM = mainPuzzle1
OBJS =  Blocks.o Board.o factory.o main.o Puzzle.o State.o

LDFLAGS += -loeglut -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/puzzle.epp > puzzle.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
