TEMPLATE = lib
CONFIG += c++11

# DEFINES = __GNUC__

INCLUDEPATH = \
    external/libxenbe \
    external/xen \
    external/kernel \
    src

HEADERS += \
    src/V4L2ToXen.hpp \
    src/FrontendBuffer.hpp \
    src/CommandHandler.hpp \
    src/CameraManager.hpp \
    src/CameraHandler.hpp \
    src/Camera.hpp \
    src/Backend.hpp


SOURCES += \
    src/V4L2ToXen.cpp \
    src/main.cpp \
    src/FrontendBuffer.cpp \
    src/CommandHandler.cpp \
    src/CameraManager.cpp \
    src/CameraHandler.cpp \
    src/Camera.cpp \
    src/Backend.cpp

DISTFILES += \
    src/CMakeLists.txt
