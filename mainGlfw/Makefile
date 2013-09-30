#
include ../makedefs

PGM = mainGlfw

OBJS = MfdDisplay.o MfdPage.o TdAzPtr.o TdElevPtr.o TestOne.o TestRotator.o TestTwo.o testw.o 

LDFLAGS += -loeInstruments -loeGlut -loeBasicGL -loeBasic -lpthread
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

EPPFLAGS += -DFONT_11_19_PATH="\"$(DATA_DIR)/fonts/11x19/normal/\"" 

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl   $(EPPFLAGS)
	cpp inputs/test2.epp >test2.edl $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
