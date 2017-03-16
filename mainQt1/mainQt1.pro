
# path to framework
OE_ROOT = $$(OE_ROOT)
isEmpty(OE_ROOT) OE_ROOT = $$PWD/../../OpenEaagles
message(OE_ROOT = $${OE_ROOT})

# version of Visual Studio, if applicable
MS_VER = vs2013-32
#MS_VER = vs2015-32

# path to 3rd party libraries
OE_3RD_PARTY_ROOT = $$(OE_3RD_PARTY_ROOT)
isEmpty(OE_3RD_PARTY_ROOT) OE_3RD_PARTY_ROOT = $$PWD/../../OpenEaagles3rdParty
message(OE_3RD_PARTY_ROOT = $${OE_3RD_PARTY_ROOT})

QT += core widgets

MAKEFILE = qtMakefile

TARGET = mainQt1
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# file types to include in project
SOURCES += *.cpp
FORMS += *.ui
HEADERS += *.hpp
OTHER_FILES += configs/*.epp

# include paths
INCLUDEPATH += \
   $${OE_ROOT}/include

# default location for intermediate files
UI_DIR = ./tmp/ui
OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# libraries
# Windows release libraries
win32:CONFIG(release, debug|release): LIBS +=        \
    # openeaagles
    -L$${OE_ROOT}/lib/                               \
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MS_VER}           \
    -loe_interop_dis                                 \
    -loe_interop                                     \
    -loe_simulation                                  \
    -loe_models                                      \
    -loe_terrain                                     \
    -loe_otw                                         \
    -loe_base                                        \
    -lccl_lib                                        \
    -ljsbsim                                         \
    # system
    -lwinmm                                          \
    -lws2_32

# Windows debug libraries
else:win32:CONFIG(debug, debug|release): LIBS +=        \
    # openeaagles
    -L$${OE_ROOT}/lib/                                  \
    -L$${OE_3RD_PARTY_ROOT}/lib/$${MS_VER}              \
    -loe_interop_dis_d                                  \
    -loe_interop_d                                      \
    -loe_simulation_d                                   \
    -loe_models_d                                       \
    -loe_terrain_d                                      \
    -loe_otw_d                                          \
    -loe_base_d                                         \
    -lccl_lib_d                                         \
    -ljsbsim_d                                          \
    # system
    -lwinmm                                             \
    -lws2_32

# Linux libraries
else:unix:!macx:!symbian: LIBS +=       \
    # openeaagles
    -L$${OE_ROOT}/lib/                  \
    -L$${OE_3RD_PARTY_ROOT}/lib/        \
    -loe_interop_dis                    \
    -loe_interop                        \
    -loe_otw                            \
    -loe_simulation                     \
    -loe_models                         \
    -loe_terrain                        \
    -loe_base                           \
    -lcigicl                            \
    -lJSBSim                            \
    # system
    -lX11 -lpthread -lrt


RESOURCES += \
    configs/data/icons.qrc
