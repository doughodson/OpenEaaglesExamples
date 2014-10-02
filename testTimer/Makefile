#
include ../makedefs

PGM = testTimer

OBJS = main.o Tester.o 

LDFLAGS += -loeBasic 
LDFLAGS += -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f ${PGM}

