#
include ../makedefs

PGM = tutorial03

OBJS = main.o Random.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f ${PGM}

