TARGET = qquicktreeviewplugin
TARGETPATH = QtQuick/TreeView

QML_IMPORT_NAME = QtQuick.TreeView
QML_IMPORT_MAJOR_VERSION = 2

QT += gui qml quick
QT += quick-private

SOURCES += \
    qquicktreeviewplugin.cpp \
    qquicktreeview.cpp \
    qquicktreemodeladaptor.cpp

HEADERS += \
    qquicktreeview_p.h \
    qquicktreeview_p_p.h \
    qquicktreemodeladaptor_p.h \

QML_FILES += TreeView.qml

OTHER_FILES += \
    qmldir \
    $$QML_FILES \

CONFIG += no_cxx_module install_qml_files builtin_resources qtquickcompiler
CONFIG += qmltypes install_qmltypes

load(qml_plugin)

