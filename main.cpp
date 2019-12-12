#include <QtGui>
#include <QtQml>
#include <QtQuick>

#include "treemodel.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    qmlRegisterType<TreeModel>("TreeModel", 1, 0, "TreeModel");
    QQmlApplicationEngine engine(QUrl("qrc:///main.qml"));
    return app.exec();
}

