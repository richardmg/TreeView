TEMPLATE = app
QT += gui qml quick widgets quick-private

RESOURCES += main.qml \
        TreeView.qml \
        default.txt

SOURCES += main.cpp \
    qquicktreeview.cpp \
    treeitem.cpp \
    treemodel.cpp \
    qquicktreemodeladaptor.cpp

OTHER_FILES += \
    main.qml

HEADERS += \
    qquicktreeview.h \
    treeitem.h \
    treemodel.h \
    qquicktreemodeladaptor_p.h
