#
include ../makedefs

PGM = testTables
OBJS = main.o

LDFLAGS += -loebase -lpthread -lrt

all: $(PGM)

$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	-rm -f $(PGM)
