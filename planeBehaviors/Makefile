#
include ../makedefs

LIB = libPlaneBehaviors.a

# form function
OBJS = \
	$(LIB)(planeBehaviorsFF.o)

# PlaneBehavior family
OBJS += \
	$(LIB)(PlaneAction.o) $(LIB)(PlaneBehaviors.o) \
	$(LIB)(PriorityArbiter.o) \
	$(LIB)(PlaneState.o) 


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

