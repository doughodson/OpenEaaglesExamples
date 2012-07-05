#
include ../../makedefs

LIB = $(OE_EXAMPLES_LIB_DIR)/libPlaneBehaviors.a

# form function
OBJS = \
	$(LIB)(formFunc.o)

# PlaneBehavior family
OBJS += \
	$(LIB)(PlaneAction.o) \
	$(LIB)(PlaneBehaviors.o) \
	$(LIB)(PriorityArbiter.o) \
	$(LIB)(PlaneState.o) 


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

