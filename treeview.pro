TEMPLATE = app
QT += gui qml quick widgets
RESOURCES += main.qml default.txt

# Input
SOURCES += main.cpp \
    treeitem.cpp \
    treemodel.cpp \
    qquicktreemodeladaptor.cpp

OTHER_FILES += \
    main.qml

HEADERS += \
    treeitem.h \
    treemodel.h \
    qquicktreemodeladaptor_p.h
