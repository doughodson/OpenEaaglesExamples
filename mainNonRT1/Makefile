
include ../makedefs

PGM = mainNonRT1

OBJS = main.o

LDFLAGS += -loeSensors -loeVehicles -loeSimulation -lJSBSim 
LDFLAGS += -loeInstruments -loeDafif
LDFLAGS += -loeBasic 
LDFLAGS += -lrt -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lpthread

CPPFLAGS += -I/usr/local/include

EPPFLAGS =  -I. \
	   -I$(DATA_DIR) \
	   -DFONT_PATH=\"$(DATA_DIR)/fonts/\" 
	   -DFONT_11_19_PATH=\"$(DATA_DIR)/fonts/11x19/normal/\" \
	   -DTEXTURES_PATH=\"$(DATA_DIR)/textures/\"

all: $(PGM)

edl:
	cpp inputs/test1.epp >test1.edl   $(EPPFLAGS)
	cpp inputs/test2.epp >test2.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)


