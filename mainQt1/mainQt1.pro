MSVC_VER = vs2015

# OpenEaagles package(s)
OE_ROOT = $$(OE_ROOT)
isEmpty(OE_ROOT) OE_ROOT = $$PWD/../../OpenEaagles
message(OE_ROOT = $${OE_ROOT})
OE_3RD_PARTY_ROOT = $$(OE_3RD_PARTY_ROOT)
isEmpty(OE_3RD_PARTY_ROOT) OE_3RD_PARTY_ROOT = $$PWD/../../OpenEaagles3rdParty
message(OE_3RD_PARTY_ROOT = $${OE_3RD_PARTY_ROOT})

QT += core widgets

TARGET = mainQt1
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# file types to include in project
SOURCES += *.cpp
FORMS += *.ui
HEADERS += *.h
OTHER_FILES += configs/*.epp

# include paths
INCLUDEPATH += \
   $${OE_ROOT}/include


# default installation of misc files
UI_DIR = ./tmp/ui
OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

# libraries
# Windows (MSVC) release libraries
win32:CONFIG(release, debug|release): LIBS +=        \
    # openeaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                  \
    -loesimulation -loemodels -loedafif              \
    -loebase                                         \
    # system
    -lwinmm                                          \
    -lws2_32

# Windows (MSVC) Debug libraries
else:win32:CONFIG(debug, debug|release): LIBS +=        \
    # openeaagles
    -L$${OE_ROOT}/lib/$${MSVC_VER}/                     \
    -loesimulation_d -loemodels_d -loedafif_d           \
    -loebase_d                                          \
    # system
    -lwinmm                                             \
    -lws2_32

# Linux libraries
else:unix:!macx:!symbian: LIBS +=                     \
    # openeaagles
    -L$${OE_ROOT}/lib/linux/                          \
    -loesimulation -loemodels -loedafif               \
    -loebase                                          \
    # system
    -lX11 -lpthread -lrt

RESOURCES += \
    data/icons.qrc
