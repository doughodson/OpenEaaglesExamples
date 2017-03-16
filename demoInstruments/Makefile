#
include ../makedefs

PGM = demoInstruments

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
	main.o

LDFLAGS += -loe_instruments -loe_glut -loe_graphics -loe_base
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

edl:
	cpp configs/testinstruments.epp >testinstruments.edl $(EPPFLAGS)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
