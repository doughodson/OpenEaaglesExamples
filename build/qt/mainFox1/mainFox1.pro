# mainFox1 OpenEaaglesExample
include(../config.pri)

# our root
MY_ROOT = $$HOME_ROOT/mainFox1

# Configuration settings
TEMPLATE = app
CONFIG += console

# destination and working directories
win32: DESTDIR = $${MY_ROOT}
else:unix:!macx:!symbian: DESTDIR = $${MY_ROOT}

#include directories and defines for FOX
unix:!macx:!symbian: \
DEFINES += FOX_1_6

OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# using Fox 1.6
DEFINES += FOX_1_6

# include paths
INCLUDEPATH +=                          \
   $${OE_ROOT}/include                  \
   $${OE_3RD_PARTY_ROOT}/include

# source files
SOURCES += \
   $${MY_ROOT}/*.cpp

# header files
HEADERS += \
   $${MY_ROOT}/*.h

# other files
OTHER_FILES += \
   $${MY_ROOT}/inputs/*.epp         \


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
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
#      links {"ftgl", LibFreetype, LibGLU, LibGL}
    -loeBasicGL_d -loeBasic_d                           \
    -loeSimulation_d -loeDafif_d -loeInstruments_d      \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lfox_d                                             \
    -lftgl_d -lfreetype2_d                              \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32                                          \
    -lshell32

# Linux libraries
else:unix:!macx:!symbian: LIBS +=                   \
   # open eaagles
   -L$${OE_ROOT}/lib/linux \
   -loeBasicGL -loeInstruments  -loeBasic \
   -loeSimulation -loeBasic -loeDafif \
   # Fox
   -lFOX-1.6 \
   # OE 3rd party
   -L$${OE_3RD_PARTY_ROOT}/lib/linux \
   -lfreetype -lftgl -lGLU -lGL \
    # system
    -lGLU -lGL -lX11                                \
    -lglut -lGLU -lGL -lX11 -lpthread -lrt   \
    -lXext

