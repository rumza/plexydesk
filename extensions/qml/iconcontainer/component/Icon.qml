import Qt 4.7
import Qt.labs.folderlistmodel 1.0

Item {
    id: iCon_base
    property alias txt : text1.text
    property int lastIndex: text1.text.lastIndexOf('.')
    property int len: text1.text.length
    property string type: text1.text.substring(lastIndex+1,len)
//    signal clicked(Text txt)
    width: 80
    height: 80
    Image {
        id: iCon_image
        width: 60
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        source: if(type == "")"images/folder.png";else if(type == "pdf")"images/pdf.png";else if(type == "txt" || type == "doc" || type == "docx")"images/doc.png";else if (type == "png")"images/png.png"; else if (type == "zip"||type=="rar"||type=="gz")"images/zip.png"
        opacity: 0.8
    }

    MouseArea {
        id: mouse_area1
//        x: 10
//        y: 0
//        width: 60
//        height: 60
//        anchors.rightMargin: -60
//        anchors.leftMargin: -60
//        anchors.bottomMargin: -60
//        anchors.top: iCon_image.bottom
//        anchors.right: iCon_image.left
//        anchors.bottom: iCon_image.top
//        anchors.left: iCon_image.right
//        anchors.topMargin: -60
	anchors.fill : parent
        opacity: 0.8
        hoverEnabled: true
//        onClicked: iCon_base.clicked(iCon_base.txt)
    }

    Text {
        id: text1
        y: 65
        x:10
        width: 78
        color: "#dbdbdb"
        text: txt.length > 13 ? txt.substring(0,10)+"..." : txt
        transformOrigin: Item.Left
        anchors.horizontalCenter: iCon_image.horizontalCenter
        font.pixelSize: 12
        opacity: 1
    }

//    Text {
//        id: text2
//        x: 18
//        y: 23
//        text: flm.folder
//        font.pixelSize: 12
//    }
    states: [
        State {
            name: "State1"
            when: mouse_area1.containsMouse == true
            PropertyChanges {
                target: iCon_base
                width: 70
                height: 70
            }

            PropertyChanges {
                target: mouse_area1
                width: 70
                height: 70
            }

            PropertyChanges {
                target: iCon_image
                width: 70
                opacity: 1
                height: 70
            }

            PropertyChanges {
                target: text1
                x: 23
                y: 56
                opacity: 0
                anchors.horizontalCenterOffset: 27
            }
        },
        State {
            name: "State2"
            when:  mouse_area1.pressed == true
            PropertyChanges {
                target: iCon_base
                x: if (type == "png" || type == "jpeg" || type == "jpg")200;else 80
                y: if (type == "png" || type == "jpeg" || type == "jpg")200;else 80
            }


        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "State1"
            reversible: true
        }
    ]

    FolderListModel
    {
        id:flm
	folder:"/home/varuna"
    }

}
