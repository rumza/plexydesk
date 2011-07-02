import Qt 4.7
import Plexy.Peel 1.0

Rectangle {
    id: peelCorner
    width: 100
    height: 100
    color: "transparent"
    Rectangle {
        id: peelImageContainer
        anchors.fill: parent
        color: "transparent"
        Image {
            id: cornerImage
            rotation: -90
            anchors.fill: parent
            source: "resources/images/peeled-corner.png"
            Behavior on opacity {
                NumberAnimation{duration: 1000; easing: Easing.InCubic}
            }
        }
        MouseArea {
            id: clickArea
            x: 50
            y: 0
            width: 50
            height: 50
            onClicked: {peeler.viewBack("DesktopBack");}
        }
    }
    states: [
        State {
            name: "default"

            PropertyChanges {
                target: cornerImage
                opacity: 0
            }
        }
    ]
    Peel
    {
        id: peeler
    }
}
