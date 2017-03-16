#
include ../makedefs

PGM = mainPuzzle2
OBJS =  Blocks.o Board.o factory.o main.o Puzzle.o State.o

LDFLAGS += -loe_gui_glut -loe_graphics -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/puzzle.epp >puzzle.edl

clean:
	-rm -f *.o
	-rm -f $(PGM)
