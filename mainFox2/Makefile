#
include ../makedefs

PGM = mainFox2

CPPFLAGS += $(FOX_DEFINES) -I$(FOX_INC_DIR) -DHAVE_GL_H
LDFLAGS  += $(FOX_LIBS)

EPPFLAGS += -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

OBJS = main.o TestWindow.o

LDFLAGS += -loesimulation -loedafif -loeinstruments -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype
LDFLAGS += -lGLU -lGL
#LDFLAGS += -lXrandr -lXi -lXinerama
LDFLAGS += -lXcursor -lXrender -lXext -lXfixes -lXft -lX11
LDFLAGS += -lfontconfig
LDFLAGS += -lpthread -lrt

all: $(PGM)

edl:
	cpp configs/foxdisplay.epp > foxdisplay.edl  $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)

