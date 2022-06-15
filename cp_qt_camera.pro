QT -= gui
QT += multimedia multimediawidgets

TEMPLATE = lib
DEFINES += CP_QT_CAMERA_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpcamera.cpp \
    cpcameraviewfinder.cpp

HEADERS += \
    cp_qt_camera_global.h \
    cpcamera.h \
    cpcamera_interface.h \
    cpcameraviewfinder.h

TRANSLATIONS += \
    cp_qt_camera_zh_CN.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
