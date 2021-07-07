#-------------------------------------------------
#
# Project created by QtCreator 2019-05-19T00:24:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab_4
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
        commands/camera/add_camera_command.cpp \
        commands/camera/move_camera_command.cpp \
        commands/camera/remove_camera_command.cpp \
        commands/camera/set_camera.cpp \
        commands/camera/transverse_axis_camera_command.cpp \
        commands/camera/longitudional_axis_camera_command.cpp \
        commands/camera/vertical_axis_camera_command.cpp \
        main.cpp \
        math/matrix.cpp \
        math/point.cpp \
        math/transform_matrix.cpp \
        objects/camera.cpp \
        objects/composite.cpp \
        drawing/qt_drawer.cpp \
        scene/scene.cpp \
        manager/scene_manager.cpp \
        manager/camera_manager.cpp \
        uploading/file_loader.cpp \
        mainwindow.cpp \
        facade/facade.cpp \
        mediator/mediator.cpp \
        objects/polygon_mesh.cpp \
   	commands/draw_command.cpp \
    	commands/shape/add_shape_command.cpp \
    	commands/shape/remove_shape_command.cpp \
    	commands/shape/transform_shape_command.cpp \
        manager/draw_manager.cpp \
        manager/transform_manager.cpp \
    manager/shape_loader.cpp \
    paintwidget.cpp \
    objects/shape.cpp \
    uploading/shape_builder.cpp

HEADERS += \
        base_manager.h \
        commands/camera/add_camera_command.h \
        commands/camera/move_camera_command.h \
        commands/camera/remove_camera_command.h \
        commands/camera/set_camera.h \
        commands/camera/vertical_axis_camera_command.h \
        commands/camera/transverse_axis_camera_command.h \
        commands/camera/longitudinal_axis_camera_command.h \
	commands/shape/add_shape_command.h \
    	commands/shape/remove_shape_command.h \
        commands/shape/transform_shape_command.h \
        commands/base_command.h \
        commands/draw_command.h \
        exceptions/camera_lack_exception.h \
        exceptions/drawer_exception.h \
        exceptions/file_open_exception.h \
        exceptions/object_search_exception.h \
        exceptions/object_type_exception.h \
        math/matrix.h \
        math/point.h \
        math/transform_matrix.h \
        objects/camera.h \
        objects/object.h \
        drawing/base_drawer.h \
        drawing/qt_drawer.h \
        scene/scene.h \
        manager/scene_manager.h \
        manager/camera_manager.h \
        uploading/base_loader_imp.h \
        uploading/file_loader.h \
        visitor/visitor.h \
        mainwindow.h \
        exceptions/base_viewer_exception.h \
        facade/facade.h \
        mediator/mediator.h \
        objects/polygon_mesh.h \
        objects/composition.h \
    manager/draw_manager.h \
    manager/transform_manager.h \
    manager/shape_loader.h \
    objects/shape.h \
    uploading/abs_shape_loader.h \
    uploading/shape_builder.h \
    exceptions/shape_build_exception.h \
    paintwidget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
