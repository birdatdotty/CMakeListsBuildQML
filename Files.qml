import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
  id: rect
  Column {
      Component {
          id: contactDelegate
          Item {
            width: 180;
            height: 20
            Row {
              spacing: 10
              Text { text: '<b>'+type+':</b>' }
              Text { text: file }
            }
          }
      }

      ListView {
//          anchors.fill: parent
          width: rect.width
          height: rect.height - rect.height/5 - 10
          model: filesListModel
          delegate: contactDelegate
    //      highlight: Rectangle { color: "lightsteelblue"; radius: 2 }
          focus: true
      }

          Rectangle {
              anchors.margins: 5
              anchors.bottom: rect.bottom
              width: parent.width
              height: rect.height/5//30
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
//                  onClicked: console.log(filesListModel.getPath())
                  onClicked: filesListModel.addFile(filesListModel.getPath(), prjTree)

              }
          }

//          text: "Добавить"
//          onClicked: console.log   (123123213123)

  }
}
