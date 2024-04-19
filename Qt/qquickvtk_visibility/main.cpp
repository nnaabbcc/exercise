#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickVTKRenderWindow.h>
#include <QQuickWindow>

#include "modelviewer.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QQuickVTKRenderWindow::setupGraphicsBackend();

  QGuiApplication app(argc, argv);

  qmlRegisterType<ModelViewer>("ModelViewer", 1, 0, "ModelViewer");

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QQmlApplicationEngine engine;
  engine.load(url);

  return app.exec();
}
