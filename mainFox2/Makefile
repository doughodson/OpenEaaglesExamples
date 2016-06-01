#
include ../makedefs

PGM = mainFox2

CPPFLAGS += $(FOX_DEFINES) -I$(FOX_INC_DIR)
LDFLAGS  += $(FOX_LIBS)

EPPFLAGS += -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

OBJS = main.o MainWindow.o Worm.o

LDFLAGS += -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype
LDFLAGS += -lGLU -lGL
#LDFLAGS += -lXft -lXrender -lXrandr -lXi -lXinerama -lXcursor -lXfixes -lXext -lX11
#LDFLAGS += -lfontconfig
LDFLAGS += -lpthread -lrt

all: $(PGM)

edl:
	cpp configs/testdisplay.epp > testdisplay.edl  $(EPPFLAGS)
	cpp configs/wormdisplay.epp > wormdisplay.edl  $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
