#-------------------------------------------------
#
# Project created by QtCreator 2019-05-19T00:24:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        commands/add_camera_command.cpp \
        commands/add_model_command.cpp \
        commands/move_camera_command.cpp \
        commands/remove_camera_command.cpp \
        commands/remove_model_command.cpp \
        commands/render_command.cpp \
        commands/set_camera.cpp \
        commands/transform_model_command.cpp \
        drawlabel.cpp \
        main.cpp \
        math/matrix.cpp \
        math/point.cpp \
        math/transform_matrix.cpp \
        objects/camera.cpp \
        objects/composite.cpp \
        objects/model.cpp \
        render/qt_drawer.cpp \
        render/renderer.cpp \
        scene/scene.cpp \
        scene/scene_manager.cpp \
        transformations/camera_manager.cpp \
        transformations/transformer.cpp \
        uploading/file_loader.cpp \
        uploading/model_builder.cpp \
        uploading/model_loader.cpp \
    mainwindow.cpp \
    commands/transverse_axis_camera_command.cpp \
    commands/longitudional_axis_camera_command.cpp \
    commands/vertical_axis_camera_command.cpp \
    facade/facade.cpp \
    intermediary/mediator.cpp \
    objects/mesh/polygon_mesh.cpp

HEADERS += \
        base_manager.h \
        commands/add_camera_command.h \
        commands/add_model_command.h \
        commands/move_camera_command.h \
        commands/remove_camera_command.h \
        commands/remove_model_command.h \
        commands/set_camera.h \
        commands/transform_model_command.h \
        drawlabel.h \
        exceptions/camera_lack_exception.h \
        exceptions/drawer_exception.h \
        exceptions/file_open_exception.h \
        exceptions/model_build_exception.h \
        exceptions/object_search_exception.h \
        exceptions/object_type_exception.h \
        math/matrix.h \
        math/point.h \
        math/transform_matrix.h \
        objects/camera.h \
        objects/model.h \
        objects/object.h \
        render/base_drawer.h \
        render/qt_drawer.h \
        render/renderer.h \
        scene/scene.h \
        scene/scene_manager.h \
        transformations/camera_manager.h \
        transformations/transformer.h \
        uploading/abs_model_loader.h \
        uploading/base_loader_imp.h \
        uploading/file_loader.h \
        uploading/model_builder.h \
        uploading/model_loader.h \
        visitor/visitor.h \
    mainwindow.h \
    commands/base_command.h \
    commands/draw_command.h \
    exceptions/base_viewer_exception.h \
    commands/vertical_axis_camera_command.h \
    commands/transverse_axis_camera_command.h \
    commands/longitudinal_axis_camera_command.h \
    facade/facade.h \
    intermediary/mediator.h \
    objects/mesh/polygon_mesh.h \
    objects/composition.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
