#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QFileSystemModel>

#include "treemodel.h"
#include "qquicktreemodeladaptor_p.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    qmlRegisterType<TreeModel>("TreeModel", 1, 0, "TreeModel");
    qmlRegisterType<QQuickTreeModelAdaptor1>("TreeModel", 1, 0, "TreeModelAdaptor");

    QQmlApplicationEngine engine;

    QFileSystemModel model;
    model.setRootPath("/");
    engine.rootContext()->setContextProperty("fileSystemModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

