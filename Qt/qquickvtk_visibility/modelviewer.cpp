#include "modelviewer.h"

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include <iostream>

static int cnt = 0;

ModelViewer::ModelViewer(QQuickItem *parent) : QQuickVTKRenderItem(parent) {
  if (cnt == 0)
    renderer()->SetBackground(1, 0, 0);
  else if (cnt == 1)
    renderer()->SetBackground(0, 1, 0);
  else
    renderer()->SetBackground(0, 0, 1);
  cnt++;
  
  vtkNew<vtkNamedColors> colors;  
  vtkNew<vtkSphereSource> source;
  
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(source->GetOutputPort());
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(0.7,0.7,0.7);

  renderer()->AddActor(actor);
  renderer()->ResetCamera();
}
