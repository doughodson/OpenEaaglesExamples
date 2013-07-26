# mainy1 OpenEaaglesExample

# using visual studio 2010 library
include(../config.pri)

# Package locations
# OpenEaagles simulation framework
OE_ROOT = $$PWD/../../../../OpenEaagles
# OpenEaagles 3rd Party dependencies
OE_3RD_PARTY_ROOT = $$PWD/../../../../OpenEaagles3rdParty
# OpenEaagles examples root
OE_EXAMPLES_ROOT = $$PWD/../../../
# our root
HOME_ROOT = $$PWD/../../../mainy1

# Configuration settings
TEMPLATE = app
CONFIG += console

# destination and working directories
win32: DESTDIR = $${HOME_ROOT}
else:unix:!macx:!symbian: DESTDIR = $${HOME_ROOT}

OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# remove deprecated windows warnings
DEFINES += _CRT_SECURE_NO_WARNINGS

# include paths
INCLUDEPATH +=                          \
   $${HOME_ROOT}                        \
   $${OE_ROOT}/include                  \
   $${OE_3RD_PARTY_ROOT}/include        \
   $${OE_EXAMPLES_ROOT}/include

# source files
SOURCES += \
   $${HOME_ROOT}/*.cpp

# header files
HEADERS += \
   $${HOME_ROOT}/*.h

# other files
OTHER_FILES += \
   $${HOME_ROOT}/inputs/*.epp         \


# Windows (MSVC) release libraries
win32:CONFIG(release, debug|release): LIBS +=           \
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loeBasicGL -loeBasic                               \
    -loeGlut                                            \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lftgl -lfreetype2 -lfreeglut                       \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32

# Windows (MSVC) Debug libraries
else:win32:CONFIG(debug, debug|release): LIBS +=        \
    # open eaagles examples
    -L$${OE_EXAMPLES_ROOT}/lib/$${MSVC_VER}/            \
    -llibY1Panel_d                                      \
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loeBasicGL_d -loeBasic_d                           \
    -loeDis_d -loeOtw_d -loeSensors_d -loeVehicles_d    \
    -loeIoDevice_d -loeInstruments_d -loeSimulation_d   \
    -loeDafif_d                                         \
    -loeGlut_d                                          \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lftgl_d -lfreetype2_d                              \
    -lfreeglut_d                                        \
    -lJSBSim_d -lccl_d                                  \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32

# Linux libraries
else:unix:!macx:!symbian: LIBS +=                   \
    # open eaagles
    -L$${OE_ROOT}/lib/linux/                        \
    -loeBasicGL -loeBasic                           \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/linux               \
    -lftgl -lfreetype -lglut                        \
    # system
    -lGLU -lGL -lX11                                \
    -lglut -lGLU -lGL -lX11 -lpthread -lrt


