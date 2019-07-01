import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

    GroupBox {
        RowLayout {
            width: parent.width
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            ExclusiveGroup {
                id: tabPositionGroup
                onCurrentChanged: {
                    if (radioApp.checked)
                        modeSet.changed("App)))")
                    else if (radioStatic.checked)
                        modeSet.changed("StaticLib)))")
                    else if (radioDyn.checked)
                        modeSet.changed("Dyn)))")
                }
            }

            RadioButton {
                id: radioApp
                checked: true
                text: qsTr("App")
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                id: radioStatic
                text: qsTr("StaticLib")
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                id: radioDyn
                text: qsTr("DynamicLib")
                exclusiveGroup: tabPositionGroup
            }

            Connections {
                target: modeSet
                onSetActiveMode: {
                    if (mode === "App")
                        radioApp.checked = true
                    else if (mode == "StaticLib")
                        radioStatic.checked = true
                    else if (mode == "DynamicLib")
                        radioDyn.checked = true
                }
            }
        }
    }

