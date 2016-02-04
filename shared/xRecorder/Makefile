#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxRecorder.a

OBJS += \
	$(LIB)(DataRecorder.o) \
	$(LIB)(factory.o)

SUBDIRS = protobuf

all: subdirs ${OBJS}

subdirs:
	for subdir in $(SUBDIRS); do \
	  echo making $@ in $$subdir; \
	  (cd $$subdir && $(MAKE)) || exit 1; \
	done

clean:
	-rm -f *.o
	-rm -f $(LIB)

