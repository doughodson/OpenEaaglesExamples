#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxrecorder.a

OBJS += \
	DataRecorder.o \
	factory.o

SUBDIRS = protobuf

all: subdirs ${OBJS}

.PHONY: all clean subdirs $(SUBDIRS)

all: $(LIB)

$(LIB) : subdirs $(OBJS)
	ar r $(LIB) $(OBJS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	-rm -f *.o
	for subdir in $(SUBDIRS); do \
	    echo making $@ in $$subdir; \
	    (cd $$subdir && $(MAKE) $@) || exit 1; \
	done
	-rm -f $(LIB)

