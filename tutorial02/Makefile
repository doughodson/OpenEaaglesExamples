#
include ../makedefs

PGM = tutorial02

OBJS = main.o Random.o

LDFLAGS += -loeBasic -lpthread

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f ${PGM}

