#
include ../makedefs

PGM = tutorial01

OBJS = main.o

LDFLAGS += -loe_base -lpthread

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:
	@echo "No input files to process"

clean:
	-rm -f *.o
	-rm -f $(PGM)
