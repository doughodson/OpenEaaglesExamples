#
include ../makedefs

PGM = demoInstruments

OBJS =  \
	inst_tests/TestAdi2.o \
	inst_tests/TestAdi.o \
	inst_tests/TestAlt.o \
	inst_tests/TestButtons.o \
	inst_tests/TestCas.o \
	inst_tests/TestCompass.o \
	inst_tests/TestDigitalGauge.o \
	inst_tests/TestEngineDial.o \
	inst_tests/TestEngPage.o \
	inst_tests/TestFtitDial.o \
	inst_tests/TestGauge1.o \
	inst_tests/TestGMeterDial.o \
	inst_tests/TestHsi.o \
	inst_tests/TestLandingGear.o \
	inst_tests/TestNozzle.o \
	inst_tests/TestOilPressure.o \
	inst_tests/TestRpmDial.o \
	inst_tests/TestSpeedBrake.o \
	inst_tests/TestVVI.o \
	main.o

LDFLAGS += -loe_instruments -loe_gui_glut -loe_graphics -loe_base
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
