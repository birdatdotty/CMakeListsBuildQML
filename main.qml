import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

import QtQuick.Controls 2.4 // scrollbar
import "GenCMakeTxt.js" as CMake

Window {
    id: win
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    title: prjTree.selPrj ? "Подпроект: " + prjTree.subProject : qsTr("Выберете проект")

    Row {
        width: parent.width
        anchors.fill: parent


        TreeView {
          id: prjTreeView
          height: parent.height
          width: 180
          TableViewColumn {
            title: "Name"
            role: "name"
          }
          model: prjTree
          onActivated: prjTree.setActiveIndex(index);
        }

        Column {
            width: win.width - prjTreeView.width
            height: win.height
            x: 2
            ConfigBlock {
                height: parent.height / 2 + 40
                width: parent.width - 4
            }
            Flickable {
                y: win.height / 2 + 40
                height: 200
                ExampleConfig
                {
                    id: exampleConfig
                    width: parent.width - 4
                    height: 100
                }
                ScrollBar.vertical: ScrollBar { }
            }

        }
    }
    Connections {
        target: prjTree
        onActiveData: {
            exampleConfig.text = CMake.genCMakeTxt(path, data)
        }
    }

}
