import QtQuick 2.15
import QtQuick.Controls 2.15

import com.genesis.vtk 1.0

Item {
    anchors.fill: parent

    // Rectangle {
    //     anchors.fill: parent
    //     color: 'red'
    // }

    VTKRenderWindow {
        id: vtkwindow
        anchors.fill: parent
    }

    VTKRenderItem {
        id: vtkItem
        objectName: "ImageView"
        anchors.fill: vtkwindow
        renderWindow: vtkwindow
    }

}
