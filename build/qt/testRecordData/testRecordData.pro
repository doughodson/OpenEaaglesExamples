# testRecordData OpenEaaglesExample
include(../config.pri)

# our root
MY_ROOT = $$HOME_ROOT/testRecordData

# Configuration settings
TEMPLATE = app
CONFIG += console

# destination and working directories
win32: DESTDIR = $${MY_ROOT}
else:unix:!macx:!symbian: DESTDIR = $${MY_ROOT}

OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# include paths
INCLUDEPATH +=                          \
   $$HOME_ROOT/include                  \
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
    # OE Examples
    -L$${HOME_ROOT}/lib/$${MSVC_VER}/                   \
    -llibMyRecorder                                   \
    -llibPlaneBehaviors -llibY1Panel                \
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loeBasic -loeRecorder  -loeBasicGL           \
    -loeGlut                                          \
    -loeDis -loeOtw -loeInstruments               \
    -loeSensors -loeVehicles -loeIoDevice         \
    -loeDafif                                         \
    -loeSimulation                                    \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lftgl -lfreetype2                              \
    -lfreeglut                                        \
    -lJSBSim                                          \
    -lccl_lib                                             \
    -llibprotobuf                                     \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32

# Windows (MSVC) Debug libraries
else:win32:CONFIG(debug, debug|release): LIBS +=        \
    # OE Examples
    -L$${HOME_ROOT}/lib/$${MSVC_VER}/                   \
    -llibMyRecorder_d                                   \
    -llibPlaneBehaviors_d -llibY1Panel_d                \
    # open eaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loeBasic_d -loeRecorder_d  -loeBasicGL_d           \
    -loeGlut_d                                          \
    -loeDis_d -loeOtw_d -loeInstruments_d               \
    -loeSensors_d -loeVehicles_d -loeIoDevice_d         \
    -loeDafif_d                                         \
    -loeSimulation_d                                    \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MSVC_VER}-32/        \
    -lftgl_d -lfreetype2_d                              \
    -lfreeglut_d                                        \
    -lJSBSim_d                                          \
    -lccl_lib_d                                             \
    -llibprotobuf_d                                     \
    # system
    -lwinmm                                             \
    -lws2_32                                            \
    -ladvapi32

# Linux libraries
else:unix:!macx:!symbian: LIBS +=                   \
   # OE Examples
    -L$${HOME_ROOT}/lib/linux/                   \
    -llibMyRecorder \
    -llibY1Panel                \
     # open eaagles
    -L$${OE_ROOT}/lib/linux/                        \
    -loeBasicGL \
    -loeInstruments \
    -loeSimulation -loeBasic -loeSensors  -loeDafif \
    -loeIoDevice \
    -loeVehicles \
    -loeRecorder \
    -loeOtw \
    -loeGlut \
    -loeDis \
    # oe 3rd party
    -L$${OE_3RD_PARTY_ROOT}/lib/linux               \
    -lftgl -lfreetype -lglut                        \
    -lJSBSim \
    -lcigicl \
    -lprotobuf \
    # system
    -lGLU -lGL -lX11                                \
    -lglut -lGLU -lGL -lX11 -lpthread -lrt


