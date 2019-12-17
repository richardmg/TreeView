TEMPLATE = app
QT += gui qml quick widgets quick-private

RESOURCES += main.qml \
        TreeView.qml \
        default.txt

SOURCES += main.cpp \
    qquicktreeview.cpp \
    qquicktreemodeladaptor.cpp

OTHER_FILES += \
    main.qml

HEADERS += \
    qquicktreeview.h \
    qquicktreemodeladaptor_p.h
