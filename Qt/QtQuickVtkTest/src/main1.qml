// import related modules
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

// import the VTK module
import com.genesis.vtk 1.0

// window containing the application
ApplicationWindow {
  id: window
  // title of the application
  title: qsTr("VTK QtQuick App")
  width: 400
  height: 400
  color: palette.window

  SystemPalette {
    id: palette
    colorGroup: SystemPalette.Active
  }

  Rectangle {
    x: parent.width / 4
    y: parent.height / 4
    width: parent.width / 2
    height: parent.height / 2
    color: 'green'
  }

  // Instantiate the vtk render window
  VTKRenderWindow {
    id: vtkwindow
    anchors.fill: parent
  }

  // add one or more vtk render items
  VTKRenderItem {
    objectName: "ConeView"
    x: parent.width / 2
    y: parent.height / 2
    width: parent.width / 2
    height: parent.height / 2
    // Provide the handle to the render window
    renderWindow: vtkwindow
  }

  VTKRenderItem {
    objectName: "ImageView"
    x: 0
    y: 0
    width: parent.width / 2
    height: parent.height / 2
    // Provide the handle to the render window
    renderWindow: vtkwindow
  }

}