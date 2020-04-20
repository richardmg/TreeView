#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QFileSystemModel>

#include "treemodel.h"
#include "qquicktreeview_p.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    qmlRegisterType<QQuickTreeView>("QtQuick.TreeView", 2, 15, "TreeView");

    QQmlApplicationEngine engine;
    QQmlFileSelector* selector = new QQmlFileSelector(&engine);
    selector->setExtraSelectors(app.arguments());

    QFileSystemModel model;
    model.setRootPath("/");
    engine.rootContext()->setContextProperty("fileSystemModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

