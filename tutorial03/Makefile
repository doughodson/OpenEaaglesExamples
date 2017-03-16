#
include ../makedefs

PGM = tutorial03

OBJS = main.o Random.o

LDFLAGS += -loe_base -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f $(PGM)
