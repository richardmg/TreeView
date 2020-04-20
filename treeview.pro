TEMPLATE = app

QT += gui qml quick widgets
QT += quick-private

RESOURCES += \
    main.qml \
    TreeView.qml \
    +style1/TreeView.qml

SOURCES += \
    main.cpp \
    qquicktreeview.cpp \
    qquicktreemodeladaptor.cpp

HEADERS += \
    qquicktreeview_p.h \
    qquicktreeview_p_p.h \
    qquicktreemodeladaptor_p.h \
