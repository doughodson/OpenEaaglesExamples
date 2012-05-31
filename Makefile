
include makedefs

# graphic oriented examples
APPLICATIONS =  mainw
APPLICATIONS += mainz1 mainz2 
APPLICATIONS += mainfd1 mainfd2
APPLICATIONS += mainEfis
APPLICATIONS += mainGL

# Non-real-time simulation
APPLICATIONS += mainNonRT1

# terrain database loader
APPLICATIONS += mainTerrain

# AI development examples 
APPLICATIONS += mainPuzzle1 mainPuzzle2

# Ir example
APPLICATIONS += mainIr

# simple simulation examples
APPLICATIONS += mainSim1 mainSim2 mainSim3 mainSim4

# radar and ground mapping radar examples
APPLICATIONS += mainx9 mainGndMapRdr

# plane behavior library and ubf example
APPLICATIONS += planeBehaviors
APPLICATIONS += mainUbf1

#
APPLICATIONS += mainVmap
#
APPLICATIONS += mainy1

# test table, state machines, events and timer
APPLICATIONS += testTables
APPLICATIONS += testStateMach
APPLICATIONS += testEvents
APPLICATIONS += testTimer

# device I/O test program
APPLICATIONS += testIo

# Matrix test program
APPLICATIONS += testMatrix

# Random distributions tests
APPLICATIONS += testRng

# Nav functions tests
APPLICATIONS += testNav

# network testing
APPLICATIONS += testNet

# linear systems package
APPLICATIONS += testLinearSys

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


