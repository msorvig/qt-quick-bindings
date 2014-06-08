import QtQuick 2.0
import ObjcBridge 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        id : text
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    NSSlider {
        id : rateSlider
        x : 10
        y : 10
        width : 400
        height : 40

        minValue : 0
        maxValue : 100
    }

    AVPlayer {
        id : thePlayer
        initWithURL: "/Users/msorvig/Desktop/chicken.mov"
        rate : rateSlider.floatValue / 100
    }

    AVPlayerView {
        player : thePlayer
        showsFullScreenToggleButton : true

        x : 50
        y : 50

        width : 300
        height : 250
    }
}
