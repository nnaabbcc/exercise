import QtQuick 2.15
import QtQuick.Controls 2.15
import com.genesis.vtk 1.0

Item {
    anchors.fill: parent

    SwipeView {
        id: swipeView
        anchors.fill: parent

        Item {
            VTKRenderItem {
                objectName: "ImageView"
                anchors.fill: parent
                renderWindow: vtkWindow
            }
        }

        Item {
            VTKRenderItem {
                objectName: "ImageView"
                anchors.fill: parent
                renderWindow: vtkWindow
            }
        }

        Item {
            VTKRenderItem {
                objectName: "ImageView"
                anchors.fill: parent
                renderWindow: vtkWindow
            }
        }

        Item {
            VTKRenderItem {
                objectName: "ImageView"
                anchors.fill: parent
                renderWindow: vtkWindow
            }
        }
    }

    VTKRenderWindow {
        id: vtkWindow
        anchors.fill: swipeView
    }

    Label {
        text: swipeView.currentIndex
        anchors.centerIn: parent
        color: 'white'
        font.pixelSize: 100
    }

}
