
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

.PHONY: all clean $(LIBRARIES)

all: $(LIBRARIES)

$(LIBRARIES):
	$(MAKE) -C $@

edl:

clean:
	for subdir in $(LIBRARIES); do \
	    echo $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done

