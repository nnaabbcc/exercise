import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.genesis.vtk 1.0

Item {
    anchors.fill: parent

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 50

        TabButton {
            text: 'Tab 1'
        }

        TabButton {
            text: 'Tab 2'
        }

        TabButton {
            text: 'Tab 3'
        }
    }

    StackLayout {
        id: stack
        anchors.top: tabBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: tabBar.currentIndex

        Rectangle {
            color: 'red'
        }

        Rectangle {
            color: 'green'
        }

        Item {
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

            Button {
                text: 'Button'
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.bottomMargin: 20
                anchors.rightMargin: 20
            }
        }

    }

}
