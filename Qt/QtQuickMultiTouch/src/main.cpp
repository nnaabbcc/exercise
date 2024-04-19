
#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickView>

int main1(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine("qrc:/main4.qml");

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}

int main(int argc, char**argv)
{
    return main1(argc, argv);
}
