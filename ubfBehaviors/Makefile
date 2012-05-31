#
include ../makedefs

LIB = libubfBehaviors

# form function
OBJS = \
	$(LIB)(ubfBehaviorsFF.o)

# PlaneBehavior family
OBJS += \
	$(LIB)(PlaneAction.o) $(LIB)(PlaneBehaviors.o) \
	$(LIB)(PriorityArbiter.o) \
	$(LIB)(PlaneState.o) 


all: ${OBJS}

clean:
	-rm -f *.o
	-rm -f $(LIB)

