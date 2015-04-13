#
include ../makedefs

PGM = mainFltk1

CPPFLAGS += -I/usr/include/Fl

OBJS = FltkDisplay.o MainWindow.o GLWindow.o FltkStation.o main.o

LDFLAGS += -loeSimulation -loeInstruments -loeDafif  -loeBasicGL -loeBasic 
LDFLAGS += -lfltk_images -lfltk_gl -lfltk
LDFLAGS += -lfreetype -lftgl -lGLU -lGL
LDFLAGS += -lpthread -lX11 -lXft
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM) 

edl:
	cpp configs/test.epp > test.edl $(EPPFLAGS)


$(PGM): $(OBJS)
	g++ -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)

