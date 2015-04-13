#
include ../makedefs

PGM = testMatrix
OBJS =  main.o

LDFLAGS += -loeBasic -lX11
#LDFLAGS += -lXi -lXmu 

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:

clean:
	-rm -f *.o
	for subdir in $(SUBDIRS); do \
	    echo making $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done
	-rm -f $(PGM)
