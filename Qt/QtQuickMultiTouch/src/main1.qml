
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15



ApplicationWindow {
    id: window

    title: qsTr("QtQuick Multi Touch App")
    width: 800
    height: 800

    Rectangle {
        anchors.fill: parent
        color: 'red'

        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 0.8
            height: parent.height * 0.8
            color: 'blue'

            MultiPointTouchArea {
                anchors.fill: parent
                minimumTouchPoints: 3
                maximumTouchPoints: 3

                onPressed: {
                    console.log('Outer Pressed ', window.touchPointsToString(touchPoints))
                }

                onReleased: {
                    console.log('Outer Released ', window.touchPointsToString(touchPoints))
                }

                onTouchUpdated: {
                    console.log('Outer TouchUpdated ', window.touchPointsToString(touchPoints))
                }

                onUpdated: {
                    console.log('Outer Updated ', window.touchPointsToString(touchPoints))
                }

                onCanceled: {
                    console.log('Outer Canceled ', window.touchPointsToString(touchPoints))
                }

                Rectangle {
                    anchors.centerIn: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8
                    color: 'green'

                    MultiPointTouchArea {
                        anchors.fill: parent
                        minimumTouchPoints: 2
                        maximumTouchPoints: 2

                        onPressed: {
                            console.log('Inter Pressed ', window.touchPointsToString(touchPoints))
                        }

                        onReleased: {
                            console.log('Inter Released ', window.touchPointsToString(touchPoints))
                        }

                        onTouchUpdated: {
                            console.log('Inter TouchUpdated ', window.touchPointsToString(touchPoints))
                        }

                        onUpdated: {
                            console.log('Inter Updated ', window.touchPointsToString(touchPoints))
                        }

                        onCanceled: {
                            console.log('Inter Canceled ', window.touchPointsToString(touchPoints))
                        }

                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                console.log('Mouse Pressed', mouse.x, mouse.y)
                            }

                            onPositionChanged: {
                                console.log('Mouse Position Changed', mouse.x, mouse.y)
                            }

                            onReleased: {
                                console.log("Mouse Released", mouse.x, mouse.y)
                            }

                            onCanceled: {
                                console.log("Mouse Canceled")
                            }

                            onWheel: {
                                console.log("Mouse Wheel")
                            }
                        }
                    }
                }
            }
        }
    }

    function touchPointsToString(touchPoints)
    {
        var str = touchPoints.length;
        for (const p of touchPoints) {
            str += ";" + p.pointId + "," + p.x + "," + p.y + "," + p.pressed;
        }
        return str;
    }

}