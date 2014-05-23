import QtQuick 2.1

Rectangle {
    width: 360
    height: 360
    Text {
        id : text
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
