#
include ../makedefs

PGM = mainFltk1

OBJS = Display.o MainWindow.o GLWindow.o Station.o mainFltk1.o

LDFLAGS += -loeSimulation -loeInstruments -loeDafif  -loeBasicGL -loeBasic 
LDFLAGS += -lfltk_images -lfltk_gl -lfltk
LDFLAGS += -lfreetype -lftgl -lGLU -lGL
LDFLAGS += -lpthread -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM) 

edl:
	cpp inputs/test.epp > test.edl   $(EPPFLAGS)


$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)

