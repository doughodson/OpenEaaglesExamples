# OpenEaagles planeBehaviors library profile

# Define the Visual studio compiler version we wish to use (Windows only)
include(../config.pri)

# Static library configuration
TEMPLATE = lib
CONFIG += static

# Store our objects in a temporary location
OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# destination and working directories
win32: DESTDIR = $${HOME_ROOT}/lib/$${MSVC_VER}/
else:unix:!macx:!symbian: DESTDIR = $${HOME_ROOT}/lib/linux

# Target names
win32:CONFIG(release, debug|release): TARGET = libPlaneBehaviors
else:win32:CONFIG(debug, debug|release): TARGET = libPlaneBehaviors_d
else:unix:!macx:!symbian: TARGET = libPlaneBehaviors

# Include paths
INCLUDEPATH += \
   $${OE_ROOT}/include            \
   $${OE_3RD_PARTY_ROOT}/include  \
   $${HOME_ROOT}/include

# Header files
HEADERS += \
   $${HOME_ROOT}/include/planeBehaviors/*.h

# Source files
SOURCES += \
   $${HOME_ROOT}/src/planeBehaviors/*.cpp

