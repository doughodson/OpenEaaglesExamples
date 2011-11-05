#
include ../makedefs

PGM = mainFox1

CPPFLAGS += -DFOX_1_6 -I/usr/include/fox-1.6

EPPFLAGS += -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

OBJS = mainFox1.o Application.o FoxDisplay.o MainWindow.o FoxStation.o Worm.o

LDFLAGS += -loeSimulation -loeDafif -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lFOX-1.6
LDFLAGS += -lftgl -lfreetype
LDFLAGS += -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

all: $(PGM)

edl:
	cpp inputs/testfox.epp >testfox.edl  $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
