#
include ../makedefs


#
CPPFLAGS += -DFOX_1_6
CPPFLAGS += -I/usr/include/fox-1.6

EPPFLAGS += -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

PGM = mainfox

OBJS = mainFox1.o Application.o Display.o formFunc.o MainWindow.o Station.o Worm.o

LDFLAGS += -loeSimulation -loeDafif -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lFOX-1.6
LDFLAGS += -lftgl -lfreetype
LDFLAGS += -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu

all: $(PGM)

edl:
	cpp testfox.epp >testfox.edl  $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
