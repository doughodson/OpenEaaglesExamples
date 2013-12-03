
include makedefs

# shared libraries
APPLICATIONS = shared-libs

# graphic oriented examples
APPLICATIONS += mainw
APPLICATIONS += mainz1 mainz2 
APPLICATIONS += mainfd1 mainfd2
APPLICATIONS += mainEfis
APPLICATIONS += mainGL

# non-real-time simulation
APPLICATIONS += mainNonRT1

# terrain database loader
APPLICATIONS += mainTerrain

# AI development examples
APPLICATIONS += mainPuzzle1 mainPuzzle2

# IR example
APPLICATIONS += mainIr

# simple simulation examples
APPLICATIONS += mainSim1 mainSim2 mainSim3 mainSim4

# ground mapping radar example
APPLICATIONS += mainGndMapRdr

# ubf example
APPLICATIONS += mainUbf1

# example demonstrates Laero model and autopilot functionality
APPLICATIONS += mainLaero

#
APPLICATIONS += mainy1

# test table, state machines, events and timer
APPLICATIONS += testTables
APPLICATIONS += testStateMach
APPLICATIONS += testEvents
APPLICATIONS += testTimer

# radar test program
APPLICATIONS += testRadar

# device I/O test program
APPLICATIONS += testIoHandler

# matrix test program
APPLICATIONS += testMatrix

# random distributions tests
APPLICATIONS += testRng

# navigation tests
APPLICATIONS += testNavigation

# network handler testing
APPLICATIONS += testNetHandler

# linear systems package
APPLICATIONS += testLinearSys

# data recorder read/write tests
APPLICATIONS += testRecordData
APPLICATIONS += testRecorderRead
APPLICATIONS += testRecorderWrite

# tutorial examples
APPLICATIONS += tutorial01
APPLICATIONS += tutorial02
APPLICATIONS += tutorial03
APPLICATIONS += tutorial04
APPLICATIONS += tutorial05
APPLICATIONS += tutorial06
APPLICATIONS += tutorial07
APPLICATIONS += tutorial08

all:
	for subdir in $(APPLICATIONS); do \
	  echo making $@ in $$subdir; \
	  (cd $$subdir && $(MAKE)) || exit 1; \
	done


edl:
	-rm -f *.o
	for subdir in $(APPLICATIONS); do \
	    echo $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done

clean:
	-rm -f *.o
	for subdir in $(APPLICATIONS); do \
	    echo $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done

