# mainFltk1 OpenEaaglesExample

# using visual studio 2010 library
include(../config.pri)

# Package locations
# OpenEaagles simulation framework
OE_ROOT = $$PWD/../../../../OpenEaagles
# OpenEaagles 3rd Party dependencies
OE_3RD_PARTY_ROOT = $$PWD/../../../../OpenEaagles3rdParty
# our root
HOME_ROOT = $$PWD/../../../mainFltk1

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
   $${OE_3RD_PARTY_ROOT}/include

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
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32

# Windows (MSVC) Debug libraries
else:win32:CONFIG(debug, debug|release): LIBS +=        \
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loeInstruments_d                                   \
    -loeBasicGL_d -loeBasic_d                           \
    -loeSimulation_d                                    \
    -loeDafif_d                                         \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lftgl_d -lfreetype2_d                              \
    -lfltk_images                                       \
    -lfltk_gl                                           \
    -lfltk                                              \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -lOle32                                             \
    -lUuid                                              \
    -lComCtl32                                          \
    -lGdi32                                             \
    -lComDlg32                                          \
    -lShell32                                           \
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


