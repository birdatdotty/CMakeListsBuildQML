import QtQuick 2.0

ListView {
    id: view

    height: parent.height
    model: componentsModel

    delegate: Item {
      id: listDelegate

      property var view: ListView.view

      width: view.width
      height: parent.parent.height/5 //40

      Rectangle {
        anchors.margins: 5
        anchors.fill: parent
        radius: height / 8
        color: model.active? "lightgreen" : "pink"
        border {
          color: model.active? "green" : "deeppink"
          width: 1
        }

        Text {
          anchors.centerIn: parent
          text: "%1%2".arg(model.text).arg(active?" - OK":"")
          font.bold: true
        }

        MouseArea {
          anchors.fill: parent
          onClicked: {
            view.currentIndex = model.index
            active = !active
          }
        }

      }

    }

}
