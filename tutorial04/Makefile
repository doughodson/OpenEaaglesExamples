#
include ../makedefs

PGM = tutorial04

OBJS = main.o Random.o Exp.o Uniform.o

LDFLAGS += -loe_base -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f $(PGM)
