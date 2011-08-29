#
include ../makedefs

PGM = mainz1

OBJS =  \
	TestAdi2.o \
	TestAdi.o \
	TestAlt.o \
	TestButtons.o \
	TestCas.o \
	TestCompass.o \
	TestDigitalGauge.o \
	TestEngineDial.o \
	TestEngPage.o \
	TestFtitDial.o \
	TestGauge1.o \
	TestGMeterDial.o \
	TestHsi.o \
	TestLandingGear.o \
	TestNozzle.o \
	TestOilPressure.o \
	TestRpmDial.o \
	TestSpeedBrake.o \
	TestVVI.o \
	testz.o

LDFLAGS += -lpthread -loeInstruments -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp inputs/testinstruments.epp >testinstruments.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)

