#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QFileSystemModel>

#include "qquicktreeview_p.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    QFileSystemModel model;
    model.setRootPath("/");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("fileSystemModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

