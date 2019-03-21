#include <QApplication>
#include <QQuickView>
#include <QSurfaceFormat>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <q3dsruntimeglobal.h>

#include "caninterface.h"

int main(int argc, char *argv[])
{
    CanInterface *myInterface = new CanInterface();

    qputenv("QSG_INFO", "1");
    QApplication app(argc, argv);

    // Use the ideal format (i.e. OpenGL version and profile) recommended by
    // the Qt 3D Studio runtime. Without this the format set on the QQuickView
    // would be used instead.
    QSurfaceFormat::setDefaultFormat(Q3DS::surfaceFormat());

    QQuickView viewer;
    viewer.setSource(QUrl("qrc:/main.qml"));

    viewer.engine()->rootContext()->setContextProperty(QStringLiteral("canObject"), &myInterface->signalmapping.canparser);

    viewer.setTitle(QStringLiteral("GÜNSEL DEMO"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.resize(1280, 480);
    viewer.setColor("#000");
    viewer.show();

    myInterface->run();

    return app.exec();
}
