
include ../makedefs

PGM = mainSim2

OBJS = main.o

LDFLAGS += -loeDis -loeSensors -loeVehicles -loeSimulation -lJSBSim 
LDFLAGS += -loeInstruments -loeOtw -loeDafif
LDFLAGS += -loeBasicGL -loeBasic -lrt -lcigicl 
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
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
	cpp inputs/test3.epp >test3.edl   $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS) 

clean:
	-rm -f *.o
	-rm -f $(PGM)


