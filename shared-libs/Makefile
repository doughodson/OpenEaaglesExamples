
# -----------------------------------------------------------------
# Library         : Description
# -----------------------------------------------------------------
# xBehaviors      : eXample UBF behaviors
# xRecorder       : eXample data recorder extension
# xPanel          : eXample instrument panel
# xZmqHandlers    : eXample ZeroMQ-based network handler
#
LIBRARIES  = xBehaviors
LIBRARIES += xRecorder
LIBRARIES += xPanel
LIBRARIES += xZmqHandlers

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

