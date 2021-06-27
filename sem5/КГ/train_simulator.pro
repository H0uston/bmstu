QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/scene.cpp \
    model/train.cpp \
    model/tree.cpp \
    model/vector.cpp \
    render_manager/camera.cpp \
    render_manager/clipper.cpp \
    model/ground.cpp \
    main.cpp \
    mainwindow.cpp \
    math/matrix.cpp \
    model/model.cpp \
    model/model_manager.cpp \
    io/parser.cpp \
    model/point.cpp \
    model/polygon.cpp \
    model/triangle.cpp \
    render_manager/clipper_cube.cpp \
    render_manager/paintwidget.cpp \
    render_manager/render_manager.cpp \
    render_manager/zbuffer.cpp

HEADERS += \
    model/scene.h \
    model/train.h \
    model/tree.h \
    model/vector.h \
    render_manager/camera.h \
    render_manager/clipper.h \
    config.h \
    model/ground.h \
    mainwindow.h \
    math/matrix.h \
    model/model.h \
    model/model_manager.h \
    io/parser.h \
    model/point.h \
    model/polygon.h \
    model/triangle.h \
    render_manager/clipper_cube.h \
    render_manager/paintwidget.h \
    render_manager/render_manager.h \
    render_manager/zbuffer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
