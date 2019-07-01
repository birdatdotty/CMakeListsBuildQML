import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

Column {
    id: column1
    BuildMode {
        width: parent.width
        title: "Вариант сборки:"
    }

    Row {
        spacing: 5
        Components {
            id: components
            height: win.height/2 //200
            width: 200
//                visible: false
        }


        Files {
            id: sources
            height: win.height/2 //200
            width: 200
//                visible: false
        }

        Dirs {
            id: dirs
            height: win.height/2 //200
            width: 200
//                visible: false
        }
    }
}
