import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle{
  id: rect
  Component {
      id: dirsDelegate
      Item {
        height: 20
        Row {
            spacing: 5
            Image { source: "qrc:/system-sharing.png" }
            Text { text: dir }
        }
      }
  }

  Column {
      ListView {
//          anchors.fill: parent
          width: rect.width
          height: rect.height - 35

          model: dirsModel
          delegate: dirsDelegate
          highlight: Rectangle { color: "lightsteelblue"; radius: 2 }
      }
      Rectangle {
//              anchors.margins: 5
//          anchors.bottom: rect.bottom
          width: rect.width
          height: 30
          radius: height / 8
          color: "lightgreen"
          border {
            color: "green"
            width: 1
          }
          Text {
              anchors.centerIn: parent
              font.bold: true
              text: qsTr("Добавить")
          }
          MouseArea {
              anchors.fill: parent
//                  onClicked: console.log("RECTANGLE")
              onClicked: dirsModel.addDir(dirsModel.getPath())

          }
      }
  }
}
