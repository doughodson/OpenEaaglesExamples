#
include ../makedefs

PGM = mainFox1

CPPFLAGS += $(FOX_DEFINES) -I$(FOX_INC_DIR)
LDFLAGS  += $(FOX_LIBS)

EPPFLAGS += -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

OBJS = mainFox1.o Application.o FoxDisplay.o MainWindow.o FoxStation.o Worm.o

LDFLAGS += -loeSimulation -loeDafif -loeInstruments -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype
LDFLAGS += -lGLU -lGL -lX11
LDFLAGS += -lpthread -lrt

all: $(PGM)

edl:
	cpp configs/testfox.epp >testfox.edl  $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
