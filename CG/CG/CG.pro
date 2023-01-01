QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    camera.cpp \
    color.cpp \
    engine.cpp \
    figure.cpp \
    lamp.cpp \
    main.cpp \
    matrix.cpp \
    shaders.cpp \
    widget.cpp

HEADERS += \
    camera.h \
    color.h \
    engine.h \
    figure.h \
    lamp.h \
    matrix.h \
    shaders.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

