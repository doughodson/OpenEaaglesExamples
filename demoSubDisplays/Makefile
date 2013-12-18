#
include ../makedefs

PGM = demoSubDisplays

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


LDFLAGS += -loeInstruments -loeGlut -loeBasicGL -loeBasic
LDFLAGS += -lftgl -lfreetype -lglut -lGLU -lGL -lX11 -lpthread
#LDFLAGS += -lXi -lXmu
LDFLAGS += -lrt

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $(PGM) $(OBJS) $(LDFLAGS)

edl:
	cpp configs/test.epp >test.edl $(EPPFLAGS)

clean:
	-rm -f *.o
	for subdir in $(SUBDIRS); do \
	    echo making $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done
	-rm -f $(PGM)


