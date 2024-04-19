import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.1
import VTK 9.1
import ModelViewer 1.0

ApplicationWindow {
    visible: true
    width: 600
    height: 600
    color: palette.window

    Row {
        Label {
            text: "red"
            color: "white"
        }
        CheckBox {
            id: checkbox1
            checked: true
        }
        Label {
            text: "green"
            color: "white"
        }
        CheckBox {
            id: checkbox2
            checked: true
        }
        Label {
            text: "blue"
            color: "white"
        }
        CheckBox {
            id: checkbox3
            checked: true
        }
        Label {
            text: "red+green"
            color: "white"
        }
        CheckBox {
            id: checkbox4
            checked: true
        }
    }

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

    VTKRenderWindow {
        id: vtkwindow
        x: 0
        y: 50
        width: 600
        height: 550
    }

    ColumnLayout {
        anchors.fill: vtkwindow

        RowLayout {
            visible: checkbox4.checked

            ModelViewer {
                visible: checkbox1.checked
                objectName: "modelViewer1"
                renderWindow: vtkwindow
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ModelViewer {
                visible: checkbox2.checked
                objectName: "modelViewer2"
                renderWindow: vtkwindow
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ModelViewer {
            visible: checkbox3.checked
            objectName: "modelViewer3"
            renderWindow: vtkwindow
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    /*
    // this is for comparison with rectangles instead of renderitems
    ColumnLayout {
        anchors.fill: vtkwindow

        RowLayout {
            visible: checkbox4.checked

            Rectangle {
                visible: checkbox1.checked
                color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Rectangle {
                visible: checkbox2.checked
                color: "green"
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        Rectangle {
            visible: checkbox3.checked
            color: "blue"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
    */
}
