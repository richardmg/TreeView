#include <QtGui>
#include <QtQml>
#include <QtQuick>

#include "treemodel.h"
#include "treetotablemodel.h"
#include "qquicktreemodeladaptor_p.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    qmlRegisterType<TreeModel>("TreeModel", 1, 0, "TreeModel");
    qmlRegisterType<TreeToTableModel>("TreeModel", 1, 0, "TreeToTableModel");
    qmlRegisterType<QQuickTreeModelAdaptor1>("TreeModel", 1, 0, "TreeModelAdaptor");

    QQmlApplicationEngine engine(QUrl("qrc:///main.qml"));
    return app.exec();
}

