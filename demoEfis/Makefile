#
include ../makedefs

PGM = demoEfis

OBJS = TestElectronic.o TestMechanical.o main.o

LDFLAGS += -loe_gui_glut -loe_instruments -loe_graphics -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/glutdisplay.epp > glutdisplay.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
