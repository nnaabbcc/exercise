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
#include <QQuickVTKItem.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkGlyph3D.h>
#include <vtkCamera.h>
#include <vtkSphereSource.h>
#include <vtkAppendPolyData.h>
#include <vtkClipPolyData.h>
#include <vtkPlane.h>
#include <vtkProperty.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkXMLImageDataReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkGlyph3DMapper.h>

namespace
{

    struct MyVtkItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);
        };

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();
            // Create a cone pipeline and add it to the view
           vtkNew<vtkRenderer> renderer;
           vtkNew<vtkActor> actor;
           vtkNew<vtkPolyDataMapper> mapper;
           vtkNew<vtkConeSource> cone;
           renderWindow->AddRenderer(renderer);
           mapper->SetInputConnection(cone->GetOutputPort());
           actor->SetMapper(mapper);
           renderer->AddActor(actor);
           renderer->ResetCamera();
           renderer->SetBackground2(0.7, 0.7, 0.7);
           renderer->SetGradientBackground(true);
           return vtk;
        }
    };
    vtkStandardNewMacro(MyVtkItem::Data);

    struct MyConeItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);
        };

        void onEndEvent(vtkObject *caller, unsigned long, void *)
        {
            vtkRenderWindow *renderWindow = vtkRenderWindow::SafeDownCast(caller);
            renderWindow->GetRenderers()->GetFirstRenderer()->ResetCamera();
            renderWindow->RemoveObserver(this->endEventTag);
            this->scheduleRender();
        }

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();

            // Create a cone pipeline and add it to the view
            vtkNew<vtkRenderer> renderer;
            vtkNew<vtkActor> actor;
            vtkNew<vtkPolyDataMapper> mapper;
            vtkNew<vtkConeSource> cone;
            renderWindow->AddRenderer(renderer);
            mapper->SetInputConnection(cone->GetOutputPort());
            actor->SetMapper(mapper);
            renderer->AddActor(actor);
            renderer->ResetCamera();
            renderer->SetBackground2(0.7, 0.7, 0.7);
            renderer->SetGradientBackground(true);

            endEventTag = renderWindow->AddObserver(vtkCommand::EndEvent, this, &MyConeItem::onEndEvent);

            return vtk;
        }

        unsigned long endEventTag;
    };
    vtkStandardNewMacro(MyConeItem::Data);

    struct MyWidgetItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);

            vtkNew<vtkImplicitPlaneWidget2> planeWidget;
        };

        struct Callback
        {
            void Execute(vtkObject *, unsigned long evt, void *)
            {
                if (evt == vtkCommand::InteractionEvent)
                {
                    this->Rep->GetPlane(this->Plane);
                    this->Actor->VisibilityOn();
                }

                if (evt == vtkCommand::EndEvent)
                {
                    // Once the application is up, adjust the camera, widget reps, etc.
                    this->Renderer->ResetCamera();
                    this->Rep->SetPlaceFactor(1.25);
                    this->Rep->PlaceWidget(this->Glyph->GetOutput()->GetBounds());
                    this->Renderer->GetActiveCamera()->Azimuth(20);
                    this->Renderer->GetRenderWindow()->RemoveObserver(this->EndEventTag);
                    this->pThis->scheduleRender();
                }
            }

            Callback()
            : Plane(nullptr), Actor(nullptr)
            {
            }

            vtkPlane *Plane;
            vtkActor *Actor;
            vtkGlyph3D *Glyph;
            vtkRenderer *Renderer;
            vtkImplicitPlaneRepresentation *Rep;
            MyWidgetItem *pThis;
            unsigned long EndEventTag;
        };

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();

            vtkNew<vtkRenderer> renderer;
            renderWindow->AddRenderer(renderer);

            // Create a mace out of filters.
            //
            vtkNew<vtkSphereSource> sphere;
            vtkNew<vtkGlyph3D> glyph;
            vtkNew<vtkConeSource> cone;
            glyph->SetInputConnection(sphere->GetOutputPort());
            glyph->SetSourceConnection(cone->GetOutputPort());
            glyph->SetVectorModeToUseNormal();
            glyph->SetScaleModeToScaleByVector();
            glyph->SetScaleFactor(0.25);

            // The sphere and spikes are appended into a single polydata.
            // This just makes things simpler to manage.
            vtkNew<vtkAppendPolyData> apd;
            apd->AddInputConnection(glyph->GetOutputPort());
            apd->AddInputConnection(sphere->GetOutputPort());

            vtkNew<vtkPolyDataMapper> maceMapper;
            maceMapper->SetInputConnection(apd->GetOutputPort());

            vtkNew<vtkActor> maceActor;
            maceActor->SetMapper(maceMapper);
            maceActor->VisibilityOn();

            // This portion of the code clips the mace with the vtkPlanes
            // implicit function. The clipped region is colored green.
            vtkNew<vtkPlane> plane;
            vtkNew<vtkClipPolyData> clipper;
            clipper->SetInputConnection(apd->GetOutputPort());
            clipper->SetClipFunction(plane);
            clipper->InsideOutOn();

            vtkNew<vtkPolyDataMapper> selectMapper;
            selectMapper->SetInputConnection(clipper->GetOutputPort());

            vtkNew<vtkActor> selectActor;
            selectActor->SetMapper(selectMapper);
            selectActor->GetProperty()->SetColor(0, 1, 0);
            selectActor->VisibilityOff();
            selectActor->SetScale(1.01, 1.01, 1.01);

            vtkNew<vtkImplicitPlaneRepresentation> rep;

            // The SetInteractor method is how 3D widgets are associated with the render
            // window interactor. Internally, SetInteractor sets up a bunch of callbacks
            // using the Command/Observer mechanism (AddObserver()).
            myCallback.Plane = plane;
            myCallback.Actor = selectActor;
            myCallback.Glyph = glyph;
            myCallback.Rep = rep;
            myCallback.Renderer = renderer;
            myCallback.pThis = this;

            vtk->planeWidget->SetRepresentation(rep);
            vtk->planeWidget->AddObserver(vtkCommand::InteractionEvent, &myCallback, &Callback::Execute);
            myCallback.EndEventTag = renderer->GetRenderWindow()->AddObserver(
                vtkCommand::EndEvent, &myCallback, &Callback::Execute);
            auto iren = renderWindow->GetInteractor();
            vtk->planeWidget->SetInteractor(iren);
            vtk->planeWidget->SetCurrentRenderer(renderer);
            vtk->planeWidget->SetEnabled(1);
            vtk->planeWidget->SetProcessEvents(1);

            renderer->AddActor(maceActor);
            renderer->AddActor(selectActor);

            return vtk;
        }

        Callback myCallback;
    };
    vtkStandardNewMacro(MyWidgetItem::Data);

    struct MyGeomItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);
        };

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();

            // Create a cone pipeline and add it to the view
            vtkNew<vtkRenderer> renderer;
            vtkNew<vtkActor> actor;
            vtkNew<vtkPolyDataMapper> mapper;
            vtkNew<vtkConeSource> cone;
            renderWindow->AddRenderer(renderer);
            mapper->SetInputConnection(cone->GetOutputPort());
            actor->SetMapper(mapper);
            renderer->AddActor(actor);
            renderer->ResetCamera();

            return vtk;
        }
    };
    vtkStandardNewMacro(MyGeomItem::Data);

    struct MyVolumeItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);
        };

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();

            vtkNew<vtkRenderer> renderer;
            renderWindow->AddRenderer(renderer);

            // Create a volume pipeline and add it to the view
            vtkNew<vtkSmartVolumeMapper> volumeMapper;
            vtkNew<vtkXMLImageDataReader> reader;
            const char *volumeFile = "vase_1comp.vti";
            reader->SetFileName(volumeFile);
            reader->Update();
            volumeMapper->SetInputConnection(reader->GetOutputPort());
            double scalarRange[2];
            volumeMapper->GetInput()->GetScalarRange(scalarRange);
            volumeMapper->SetAutoAdjustSampleDistances(1);
            volumeMapper->SetBlendModeToComposite();
            vtkNew<vtkPiecewiseFunction> scalarOpacity;
            scalarOpacity->AddPoint(scalarRange[0], 0.0);
            scalarOpacity->AddPoint(scalarRange[1], 0.09);
            vtkNew<vtkVolumeProperty> volumeProperty;
            volumeProperty->ShadeOff();
            volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);
            volumeProperty->SetScalarOpacity(scalarOpacity);
            vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
                volumeProperty->GetRGBTransferFunction(0);
            colorTransferFunction->RemoveAllPoints();
            colorTransferFunction->AddRGBPoint(scalarRange[0], 0.6, 0.4, 0.1);
            // colorTransferFunction->AddRGBPoint(scalarRange[1], 0.2, 0.1, 0.3);
            vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
            volume->SetMapper(volumeMapper);
            volume->SetProperty(volumeProperty);
            renderer->AddVolume(volume);
            renderer->ResetCamera();

            return vtk;
        }
    };
    vtkStandardNewMacro(MyVolumeItem::Data);

    struct MyGlyphItem : QQuickVTKItem
    {
        struct Data : vtkObject
        {
            static Data *New();
            vtkTypeMacro(Data, vtkObject);
        };

        vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override
        {
            auto vtk = vtkNew<Data>();

            vtkNew<vtkRenderer> renderer;
            renderWindow->AddRenderer(renderer);

            // Create the glyph pipeline
            vtkNew<vtkSphereSource> sphere;
            vtkNew<vtkGlyph3DMapper> glyphMapper;
            vtkNew<vtkConeSource> squad;
            glyphMapper->SetInputConnection(sphere->GetOutputPort());
            glyphMapper->SetSourceConnection(squad->GetOutputPort());
            glyphMapper->SetOrientationArray("Normals");
            vtkNew<vtkActor> glyphActor;
            glyphActor->SetMapper(glyphMapper);
            glyphActor->GetProperty()->SetDiffuseColor(0.5, 1.0, 0.8);
            renderer->AddActor(glyphActor);
            renderer->ResetCamera();

            return vtk;
        }
    };
    vtkStandardNewMacro(MyGlyphItem::Data);
}

void registerTypes()
{
    int major = 1;
    int minor = 0;
    auto uri = "com.genesis.vtk";

    // Register QML metatypes
    qmlRegisterType<QQuickVTKRenderWindow>(uri, major, minor, "VTKRenderWindow");
    qmlRegisterType<QQuickVTKRenderItem>(uri, major, minor, "VTKRenderItem");
    qmlRegisterType<QQuickVTKInteractiveWidget>(uri, major, minor, "VTKWidget");

    qmlRegisterType<MyVtkItem>(uri, 1, 0, "MyVtkItem");
    qmlRegisterType<MyConeItem>(uri, 1, 0, "MyConeItem");
    qmlRegisterType<MyWidgetItem>(uri, 1, 0, "MyWidgetItem");

    qmlRegisterType<MyGeomItem>(uri, 1, 0, "MyGeomItem");
    qmlRegisterType<MyGlyphItem>(uri, 1, 0, "MyGlyphItem");
    qmlRegisterType<MyVolumeItem>(uri, 1, 0, "MyVolumeItem");
}

int main1(int argc, char **argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine("qrc:/main1.qml");

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    window->show();

    {
        // Fetch the QQuick window using the standard object name set up in the constructor
        QQuickVTKRenderItem *qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem *>("ConeView");

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
        QQuickVTKRenderItem *qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem *>("ImageView");
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

int main2(int argc, char **argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main2.qml"));
    view->show();

    auto topLevel = view->rootObject();

    {
        QQuickVTKRenderItem *qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem *>("ImageView");
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

int main3(int argc, char **argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main3.qml"));
    view->show();

    auto topLevel = view->rootObject();

    {
        QQuickVTKRenderItem *qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem *>("ImageView");
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

int main4(int argc, char **argv)
{
    registerTypes();
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main4.qml"));
    view->resize(800, 600);
    view->show();

    auto topLevel = view->rootObject();
    auto items = topLevel->findChildren<QQuickVTKRenderItem *>("ImageView");
    for (int i = 0; i < items.size(); i++)
    {
        auto qquickvtkItem = items[i];
        vtkNew<vtkImageSlice> actor;
        vtkNew<vtkImageSliceMapper> mapper;
        vtkNew<vtkDICOMReader> reader;
        vtkNew<vtkImageMapToWindowLevelColors> wl;
        reader->SetFileName(QString("%1.dcm").arg(i + 1).toLocal8Bit().data());
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

int main5(int argc, char **argv)
{
    registerTypes();
    QQuickVTKItem::setGraphicsApi();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main5.qml"));
    view->show();

    auto topLevel = view->rootObject();

    return app.exec();
}

int main6(int argc, char **argv)
{
    registerTypes();
    QQuickVTKItem::setGraphicsApi();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main6.qml"));
    view->show();

    auto topLevel = view->rootObject();

    return app.exec();
}

int main7(int argc, char **argv)
{
    registerTypes();
    QQuickVTKItem::setGraphicsApi();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/main7.qml"));
    view->show();

    auto topLevel = view->rootObject();

    return app.exec();
}

int main(int argc, char **argv)
{
    // return main1(argc, argv);
    // return main2(argc, argv);
    // return main3(argc, argv);
    // return main4(argc, argv);
    // return main5(argc, argv);
    // return main6(argc, argv);
    return main7(argc, argv);
}
