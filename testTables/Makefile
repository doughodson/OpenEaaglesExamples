#
include ../makedefs

PGM = testTables
OBJS = testTables.o

LDFLAGS += -loeBasic -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
