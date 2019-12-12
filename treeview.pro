TEMPLATE = app
QT += gui qml quick
RESOURCES += main.qml default.txt

# Input
SOURCES += main.cpp \
    treeitem.cpp \
    treemodel.cpp \
    treetotablemodel.cpp

OTHER_FILES += \
    main.qml

HEADERS += \
    treeitem.h \
    treemodel.h \
    treetotablemodel.h
