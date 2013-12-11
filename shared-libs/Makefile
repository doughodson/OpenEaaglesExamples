

# Library         : Description
# -----------------------------------------------------------------
# xBehaviors      : eXample UBF behaviors
# xRecorder       : eXample data recorder extension
# xPanel          : eXample instrument panel
# xZeroMQ         : eXample 0MQ binding extension
#
LIBRARIES  = xBehaviors
LIBRARIES += xRecorder
LIBRARIES += xPanel
LIBRARIES += xZeroMQ

#
# Rules
#
all:
	@echo ${OE_ROOT}
	for subdir in $(LIBRARIES); do \
	  echo making $@ in $$subdir; \
	  (cd $$subdir && $(MAKE)) || exit 1; \
	done

edl:

clean:
	-rm -f *.o
	for subdir in $(LIBRARIES); do \
	    echo $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done

