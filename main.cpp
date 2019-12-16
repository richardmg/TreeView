#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QFileSystemModel>

#include "treemodel.h"
#include "qquicktreeview.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    qmlRegisterType<QQuickTreeView>("TreeView", 1, 0, "TreeView");

    QQmlApplicationEngine engine;

    QFileSystemModel model;
    model.setRootPath("/");
    engine.rootContext()->setContextProperty("fileSystemModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

