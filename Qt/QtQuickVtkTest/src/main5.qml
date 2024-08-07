// import related modules
import QtQuick 2.15

// import MyVtkItem
import com.genesis.vtk 1.0

// Item containing test items
Item {
  width: 400
  height: 400

  // a rectangle in the middle of the content area
  Rectangle {
    width: 100
    height: 100
    color: "blue"
    border.color: "red"
    border.width: 5
    radius: 10
  }

  MyVtkItem {
    objectName: "ConeView"
    x: 200
    y: 200
    width: 21
    height: 200
    focus: true

    Rectangle {
        x: 50
        y: 50
        width: 100
        height: 100
        color: 'transparent'
        border.color: 'blue'
        border.width: 2
        radius: 10
    }
  }
}
