#
include ../makedefs

PGM = testIoHandler

OBJS = Display.o Table.o factory.o main.o

LDFLAGS += -loeiodevice -loeglut -loegraphics -loebase
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

EPPFLAGS = \
	-DFONT_11_19_NORMAL_PATH=\"$(DATA_DIR)/fonts/11x19/normal/\" \
	-DFONT_11_19_UNDERLINE_PATH=\"$(DATA_DIR)/fonts/11x19/underline/\" \
	-DFONT_11_19_SPECIAL_PATH=\"$(DATA_DIR)/fonts/11x19/special/\"

all: $(PGM)

$(PGM): $(OBJS)
	g++ -o $@ $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test1.epp >test1.edl $(EPPFLAGS)
	cpp configs/test2.epp >test2.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
