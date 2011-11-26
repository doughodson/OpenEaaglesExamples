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
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f ${PGM}

