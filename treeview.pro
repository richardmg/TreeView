TEMPLATE = app

CONFIG += qmltypes
QML_IMPORT_NAME = TreeView
QML_IMPORT_MAJOR_VERSION = 2

QT += gui qml quick widgets
QT += quick-private

RESOURCES += \
    main.qml \
    TreeView.qml \

SOURCES += \
    main.cpp \
    qquicktreeview.cpp \
    qquicktreemodeladaptor.cpp

HEADERS += \
    qquicktreeview_p.h \
    qquicktreeview_p_p.h \
    qquicktreemodeladaptor_p.h \
