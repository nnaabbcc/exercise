#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickView>
#include <QQuickVTKRenderWindow.h>
#include <QQuickVTKRenderItem.h>
#include <QQuickVTKInteractiveWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkConeSource.h>
#include <vtkDICOMReader.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageData.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkNew.h>
#include <vtkVersion.h>
#include <vtkDistanceWidget.h>

void registerTypes()
{
    int major = 1;
    int minor = 0;
    auto uri = "com.genesis.vtk";

    // Register QML metatypes
    qmlRegisterType<QQuickVTKRenderWindow>(uri, major, minor, "VTKRenderWindow");
    qmlRegisterType<QQuickVTKRenderItem>(uri, major, minor, "VTKRenderItem");
    qmlRegisterType<QQuickVTKInteractiveWidget>(uri, major, minor, "VTKWidget");
}

int main1(int argc, char** argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine("qrc:/main1.qml");

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    {
        // Fetch the QQuick window using the standard object name set up in the constructor
        QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ConeView");

        // Create a cone pipeline and add it to the view
        vtkNew<vtkActor> actor;
        vtkNew<vtkPolyDataMapper> mapper;
        vtkNew<vtkConeSource> cone;
        mapper->SetInputConnection(cone->GetOutputPort());
        actor->SetMapper(mapper);
        qquickvtkItem->renderer()->AddActor(actor);
        qquickvtkItem->renderer()->ResetCamera();
        qquickvtkItem->renderer()->SetBackground(0.5, 0.5, 0.7);
        qquickvtkItem->renderer()->SetBackground2(0.7, 0.7, 0.7);
        qquickvtkItem->renderer()->SetGradientBackground(true);
        qquickvtkItem->update();
    }

    {
        QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ImageView");
        vtkNew<vtkImageSlice> actor;
        vtkNew<vtkImageSliceMapper> mapper;
        vtkNew<vtkDICOMReader> reader;
        vtkNew<vtkImageMapToWindowLevelColors> wl;
        reader->SetFileName("1.dcm");
        reader->Update();

        auto data = reader->GetOutput();
        double range[2];
        data->GetScalarRange(range);
        auto window = range[1] - range[0];
        auto level = range[0] + window / 2;
        wl->SetInputConnection(reader->GetOutputPort());
        wl->SetWindow(window);
        wl->SetLevel(level);
        wl->Update();

        mapper->SetInputConnection(wl->GetOutputPort());
        actor->SetMapper(mapper);
        qquickvtkItem->renderer()->AddActor(actor);
        qquickvtkItem->update();
    }
    return app.exec();
}

int main2(int argc, char** argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main2.qml"));
    view->show();

    auto topLevel = view->rootObject();

    {
        QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ImageView");
        qquickvtkItem->setAcceptHoverEvents(false);

        vtkNew<vtkImageSlice> actor;
        vtkNew<vtkImageSliceMapper> mapper;
        vtkNew<vtkDICOMReader> reader;
        vtkNew<vtkImageMapToWindowLevelColors> wl;
        // reader->SetFileName("1.dcm");
        reader->SetFileName("5.dcm");
        reader->Update();

        auto data = reader->GetOutput();
        double range[2];
        data->GetScalarRange(range);
        auto window = range[1] - range[0];
        auto level = range[0] + window / 2;
        wl->SetInputConnection(reader->GetOutputPort());
        wl->SetWindow(window);
        wl->SetLevel(level);
        wl->Update();

        mapper->SetInputConnection(wl->GetOutputPort());
        actor->SetMapper(mapper);
        qquickvtkItem->renderer()->AddActor(actor);

        // vtkNew<vtkDistanceWidget> distanceWidget;
        auto distanceWidget = vtkDistanceWidget::New();
        distanceWidget->CreateDefaultRepresentation();
        auto wrapper = new QQuickVTKInteractiveWidget;
        wrapper->setWidget(distanceWidget);
        qquickvtkItem->addWidget(wrapper);
        wrapper->setEnabled(true);
        // distanceWidget->On();

        qquickvtkItem->update();
    }

    return app.exec();
}


int main3(int argc, char** argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main3.qml"));
    view->show();

    auto topLevel = view->rootObject();

    {
        QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ImageView");
        vtkNew<vtkImageSlice> actor;
        vtkNew<vtkImageSliceMapper> mapper;
        vtkNew<vtkDICOMReader> reader;
        vtkNew<vtkImageMapToWindowLevelColors> wl;
        reader->SetFileName("1.dcm");
        reader->Update();

        auto data = reader->GetOutput();
        double range[2];
        data->GetScalarRange(range);
        auto window = range[1] - range[0];
        auto level = range[0] + window / 2;
        wl->SetInputConnection(reader->GetOutputPort());
        wl->SetWindow(window);
        wl->SetLevel(level);
        wl->Update();

        mapper->SetInputConnection(wl->GetOutputPort());
        actor->SetMapper(mapper);
        qquickvtkItem->renderer()->AddActor(actor);
        qquickvtkItem->update();
    }

    return app.exec();
}

int main4(int argc, char** argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main4.qml"));
    view->resize(800, 600);
    view->show();

    auto topLevel = view->rootObject();
    auto items = topLevel->findChildren<QQuickVTKRenderItem*>("ImageView");
    for (int i = 0; i < items.size(); i++)
    {
        auto qquickvtkItem = items[i];
        vtkNew<vtkImageSlice> actor;
        vtkNew<vtkImageSliceMapper> mapper;
        vtkNew<vtkDICOMReader> reader;
        vtkNew<vtkImageMapToWindowLevelColors> wl;
        reader->SetFileName(QString("%1.dcm").arg(i+1).toLocal8Bit().data());
        reader->Update();

        auto data = reader->GetOutput();
        double range[2];
        data->GetScalarRange(range);
        auto window = range[1] - range[0];
        auto level = range[0] + window / 2;
        wl->SetInputConnection(reader->GetOutputPort());
        wl->SetWindow(window);
        wl->SetLevel(level);
        wl->Update();

        mapper->SetInputConnection(wl->GetOutputPort());
        actor->SetMapper(mapper);
        qquickvtkItem->renderer()->AddActor(actor);
        qquickvtkItem->update();
    }

    return app.exec();
}

int main(int argc, char**argv)
{
    // return main1(argc, argv);
    return main2(argc, argv);
    // return main3(argc, argv);
    // return main4(argc, argv);
}
