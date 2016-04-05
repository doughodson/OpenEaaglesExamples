#
include ../makedefs

PGM = testTimer

OBJS = main.o Tester.o

LDFLAGS += -loebase
LDFLAGS += -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f $(PGM)
