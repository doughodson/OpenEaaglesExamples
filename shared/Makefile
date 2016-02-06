
# -----------------------------------------------------------------
# Library           : Description
# -----------------------------------------------------------------
# xbehaviors        : eXample UBF behaviors
# xrecorder         : eXample data recorder extension
# xpanel            : eXample instrument panel
# xzmq              : eXample ZeroMQ-based network handlers
#
LIBRARIES  = xbehaviors
LIBRARIES += xrecorder
LIBRARIES += xpanel
LIBRARIES += xzmq

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

