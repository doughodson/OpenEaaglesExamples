#
include ../makedefs

PGM = mainGlfw

OBJS = TestOne.o main.o 

LDFLAGS += -loeGlfw -loeBasicGL -loeBasic -lpthread
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
LDFLAGS += -lGLEW -lglfw3 
LDFLAGS += -lXrandr -lXxf86vm
LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

EPPFLAGS += -DFONT_11_19_PATH="\"$(DATA_DIR)/fonts/11x19/normal/\"" 

all: $(PGM)

edl:
	cpp inputs/test.epp >test.edl   $(EPPFLAGS)


$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
