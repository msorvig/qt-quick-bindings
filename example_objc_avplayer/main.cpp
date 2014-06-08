#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // workaround for QtQuick opengl / video player content issues
    // (hides opengl content, shows video)
    qputenv("QT_MAC_WANTS_LAYER", "1");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qmltest/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
