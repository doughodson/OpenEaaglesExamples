

# Library         : Description
# -----------------------------------------------------------------
# myRecorder      : Example data recorder extension
# planeBehaviors  : Example UBF behaviors
# y1panel         : Instrument panel for mainy1, mainUbf1 and testRecordData
#
LIBRARIES = myRecorder
LIBRARIES += planeBehaviors
LIBRARIES += y1panel

#
# Rules
#
all:
	@echo ${OE_ROOT}
	for subdir in $(LIBRARIES); do \
	  echo making $@ in $$subdir; \
	  (cd $$subdir && $(MAKE)) || exit 1; \
	done

clean:
	-rm -f *.o
	for subdir in $(LIBRARIES); do \
	    echo $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done

