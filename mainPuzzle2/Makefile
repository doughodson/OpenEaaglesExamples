#
include ../makedefs

PGM = mainPuzzle2
OBJS =  Blocks.o Board.o formFunc.o mainPuz.o Puzzle.o State.o

LDFLAGS += -lpthread -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp inputs/puzzle.epp >puzzle.edl

clean:
	-rm -f *.o
	for subdir in $(SUBDIRS); do \
	    echo making $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done
	-rm -f $(PGM)
