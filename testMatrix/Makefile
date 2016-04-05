#
include ../makedefs

PGM = testMatrix
OBJS =  main.o

LDFLAGS += -loebase -lX11
#LDFLAGS += -lXi -lXmu

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
