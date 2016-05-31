#
include ../makedefs

PGM = mainFltk1

OBJS = FltkDisplay.o MainWindow.o GLWindow.o FltkStation.o main.o

LDFLAGS += -loesimulation -loeinstruments -loedafif  -loegraphics -loebase
LDFLAGS += -lfltk_forms -lfltk_gl -lfltk_images -lfltk
LDFLAGS += -lfreetype -lftgl -lGLU -lGL
#LDFLAGS += -lXcursor -lXrandr -lXi -lXinerama -lX11
LDFLAGS +=  -lXfixes -lXext -lXrender -lXft -lX11
LDFLAGS += -lfontconfig
LDFLAGS += -lpthread -lrt -ldl

all: $(PGM)

edl:
	cpp configs/test.epp > test.edl $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
