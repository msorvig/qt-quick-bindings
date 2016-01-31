import QtQuick 2.1

Rectangle {
    width: 360
    height: 360

    Text {
        id : text
        text: qsTr("The number is: " + foo.bar)
        anchors.centerIn: parent
    }
}
