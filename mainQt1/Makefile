
include ../makedefs

PGM = mainQt1

EPPFLAGS +=  -I.

all: $(PGM)

$(PGM):
	qmake
	$(MAKE) -f qtMakefile

edl:
	cpp configs/test.epp > test.edl $(EPPFLAGS)

clean:
	-rm -f $(PGM)
	-rm -f qtMakefile
	-rm -rf tmp
