
include ../makedefs

PGM = mainSim1

OBJS = main.o

LDFLAGS += -lxzmq -l:libzmq.a
LDFLAGS += -loe_interop_dis -loe_interop -loe_otw -loe_models -loe_simulation
LDFLAGS += -loe_terrain -loe_base
LDFLAGS += -lcigicl -lJSBSim
LDFLAGS += -lrt -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS +=  -I.

all: $(PGM)

edl:
	cpp configs/test0.epp > test0.edl $(EPPFLAGS)
	cpp configs/test1.epp > test1.edl $(EPPFLAGS)
	cpp configs/test2.epp > test2.edl $(EPPFLAGS)
	cpp configs/test3.epp > test3.edl $(EPPFLAGS)
	cpp configs/test4.epp > test4.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
