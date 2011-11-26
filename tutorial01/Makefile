#
include ../makedefs

PGM = tutorial01

OBJS = main.o

LDFLAGS += -loeBasic -lpthread

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f ${PGM}

