# OpenEaagles Y1Panel library profile
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
win32:CONFIG(release, debug|release): TARGET = libY1Panel
else:win32:CONFIG(debug, debug|release): TARGET = libY1Panel_d
else:unix:!macx:!symbian: TARGET = libY1Panel

# Include paths
INCLUDEPATH += \
   $${OE_ROOT}/include            \
   $${OE_3RD_PARTY_ROOT}/include  \
   $${HOME_ROOT}/include

# Header files
HEADERS += \
   $${HOME_ROOT}/include/y1panel/*.h

# Source files
SOURCES += \
   $${HOME_ROOT}/src/y1panel/*.cpp

