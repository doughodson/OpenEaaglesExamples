#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libxBehaviors.a

OBJS += \
	$(LIB)(factory.o) \
	$(LIB)(PlaneAction.o) \
	$(LIB)(PlaneBehaviors.o) \
	$(LIB)(PriorityArbiter.o) \
	$(LIB)(PlaneState.o) 


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

