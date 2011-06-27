/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  : Varuna Lekamwasam <vrlekamwasam@gmail.com>
*
*  PlexyDesk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  PlexyDesk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PlexyDesk. If not, see <http://www.gnu.org/licenses/lgpl.html>
*******************************************************************************/
import Qt 4.7

Rectangle {
    id: base
    width: 300
    height: 200
    color: "#00000000"


    Rectangle {
        id: top
        x: base.x
        y: base.y
        width: 300
        height: 50
        color: "transparent"
        Behavior on opacity {
            NumberAnimation{duration: 100}
        }
        Image {
            id: image1
            anchors.fill: parent
            source: "images/top.png"
        }
    }

    Rectangle {
        id: middle501
        x: top.x
        y: 50
        width: 300
        height: 50
        color: "#00000000"
        Behavior on opacity {
            NumberAnimation{duration: 100}
        }
        Image {
            id: middle50img1
            anchors.fill: parent
            source: "images/middle-50.png"
        }
    }
    Rectangle {
        id: middle502
        x: top.x
        y: 100
        width: 300
        height: 0
        color: "#00000000"
        opacity: 1
        Behavior on height {
            NumberAnimation{duration: 100}
        }
        Image {
            id: middle50img2
            anchors.fill: parent
            source: "images/middle-50.png"
        }
    }

    Rectangle {
        id: middle100
        x: top.x
        y: 50
        width: base.width
        height: 100
        color: "transparent"
        Behavior on opacity {
            NumberAnimation{duration: 100}
        }
        Image {
            id: image2
            opacity: 0
            anchors.fill: parent
            source: "images/middle-100.png"
        }
    }

    Rectangle {
        id: bottom
        x: 0
        y: 100
        width: 300
        height: 50
        color: "transparent"
        Behavior on opacity {
            NumberAnimation{duration: 100}
        }
        Behavior on y {
            NumberAnimation{duration: 100}
        }
        Image {
            id: image3
            anchors.fill: parent
            source: "images/bottom.png"
        }
    }
    Rectangle {
        id: strecher
        x: 12
        y: 12
        width: 275
        height: 100
        color: "transparent"

        Item {
            id: menuItem
            x: 2
            y: 38
            width: parent.width -4
            height: 60

            Image {
                id: login
                x: 113
                y: 10
                width: 40
                height: 40
                anchors.horizontalCenterOffset: -30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: parent.verticalCenter
                source: "images/login.png"

                MouseArea {
                    id: clickArea1
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: hint1.opacity = 1
                    onExited: hint1.opacity = 0
                    onClicked: base.state = "ss_login"
                }
            }

            Image {
                id: searchPeople
                x: 152
                y: 10
                width: 40
                height: 40
                anchors.horizontalCenterOffset: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: parent.verticalCenter
                source: "images/searchpeople.png"

                MouseArea {
                    id: clickArea2
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: hint2.opacity = 1
                    onExited: hint2.opacity = 0
                    onClicked:{base.state = "ss_searchpeople"}
                }
            }

            Rectangle {
                id: hint1
                x: 15
                y: 50
                width: 110
                height: 19
                color: "#ffd069"
                radius: 4
                opacity: 0

                Text {
                    id: hint1Text
                    x: 22
                    y: 7
                    width: 100
                    color: "#030303"
                    text: "Login to facebook"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                }
                Behavior on opacity {
                    NumberAnimation{duration: 100}
                }
            }
            Rectangle {
                id: hint2
                x: 146
                y: 50
                width: 112
                height: 19
                color: "#ffd069"
                radius: 4
                opacity: 0

                Text {
                    id: hint2Text
                    x: 22
                    y: 7
                    width: 104
                    color: "#030303"
                    text: "Search in facebook"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                }
                Behavior on opacity {
                    NumberAnimation{duration: 100}
                }
            }
            Behavior on opacity {
                NumberAnimation{duration: 100}
            }
        }

        Item {
            id: searchPeopleItem
            x: 8
            y: 51
            width: 261
            height: 20
            opacity: 0
            Rectangle {
                id: customTextBox1
                y: 90
                width: 171
                height: 24
                color: "#e4e1e1"
                radius: 3
                anchors.left: searchPeoplePrompt.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                border.width: 1
                border.color: "#000000"

                TextInput {
                    id: text_input1
                    x: 43
                    y: 3
                    width: 165
                    height: 14
                    text: "user name"
                    clip: true
                    font.family: "Sans Serif"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    autoScroll: false
                    cursorVisible: true
                    font.pixelSize: 12
                    onAccepted: {base.state = "ss_searchpeople_res"}
                }
            }
            Text {
                id: searchPeoplePrompt
                y: 92
                text: "Search people"
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                color: "white"
            }
            Behavior on opacity {
                NumberAnimation{duration: 300}
            }
        }

        Rectangle {
            id: header
            x: 0
            y: 0
            width: parent.width
            height: 36
            color: "#617aaf"
            opacity: 1
            Behavior on height{NumberAnimation {duration: 100}}
            Image {
                id: icon
                x: 5
                y: 4
                width: 32
                height: 32
                source: "images/facebook-icon2-small.png"
            }

            Text {
                id: connectToFacebook
                x: 44
                y: 14
                color: "#ffffff"
                text: "Connect to Facebook"
                styleColor: "#170aa0"
                style: Text.Outline
                font.pixelSize: 12
            }
        }

        Rectangle {
            id: home
            x: header.width - 30
            y: header.y + 5
            width: 24
            height: 24
            color: "transparent"
            Image {
                id: homeImage
                anchors.fill: parent
                source: "images/home.png"
                opacity: 0
                Behavior on opacity{
                    NumberAnimation{duration: 200}
                }

                MouseArea {
                    id: clickHome
                    anchors.fill: parent
                    onClicked: base.state = ""
                }
            }
        }

        Item {
            id: loginItem
            x: 2
            y: 38
            width: 275
            height: 89
            opacity: 0
            Rectangle {
                id: customTextBox2
                y: 8
                width: 171
                height: 24
                color: "#e4e1e1"
                radius: 3
                anchors.left: text2.right
                anchors.verticalCenterOffset: -2
                anchors.leftMargin: 10
                anchors.verticalCenter: text1.verticalCenter
                border.width: 1
                border.color: "#000000"

                TextInput {
                    id: text_input2
                    x: 43
                    y: 3
                    width: 165
                    height: 14
                    clip: true
                    font.family: "Sans Serif"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    autoScroll: false
                    cursorVisible: true
                    font.pixelSize: 12
                }
            }
            Rectangle {
                id: customTextBox3
                x: 82
                y: 44
                width: 171
                height: 24
                color: "#e4e1e1"
                radius: 3
                anchors.left: text2.right
                anchors.verticalCenterOffset: 0
                anchors.leftMargin: 10
                anchors.verticalCenter: text2.verticalCenter
                border.width: 1
                border.color: "#000000"

                TextInput {
                    id: text_input3
                    x: 43
                    y: 3
                    width: 165
                    height: 14
                    passwordCharacter: "*"
                    echoMode: TextInput.PasswordEchoOnEdit
                    clip: true
                    font.family: "Sans Serif"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    autoScroll: false
                    cursorVisible: true
                    font.pixelSize: 12
                }
            }

            Text {
                id: text1
                x: 11
                y: 12
                color: "#ffffff"
                text: "Email"
                font.pixelSize: 12
                opacity: 1
            }

            Text {
                id: text2
                y: 43
                color: "#ffffff"
                text: "Password"
                anchors.left: text1.left
                anchors.leftMargin: 0
                font.pixelSize: 12
                opacity: 1
            }

            Rectangle {
                id: loginButton
                x: 184
                y: 67
                width: 60
                height: 19
                color: "#5e88d1"
                radius: 4
                anchors.right: customTextBox3.right
                opacity: 1

                Text {
                    id: loginText
                    x: 204
                    y: 179
                    color: "#ffffff"
                    text: "Login"
                    style: Text.Raised
                    font.bold: false
                    font.family: "DejaVu Sans"
                    font.pointSize: 9
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    opacity: 1
                }

                MouseArea {
                    id: loginButtonClick
                    anchors.fill: parent
                    opacity: 1
                }
            }
        }

        Rectangle {
            id: searchResult
            x: 8
            y: 79
            width: searchPeopleItem.width
            height: 100
            color: "#00000000"
            radius: 5
            anchors.left: searchPeopleItem.left
            anchors.leftMargin: 0
            opacity: 0

            Image {
                id: profilePic
                x: 5
                y: 25
                width: 50
                height: 50
                source: "http://graph.facebook.com/varunarl/picture"
                opacity: 0
                Behavior on opacity {
                    NumberAnimation{duration: 1000}
                }
                onStatusChanged: if (profilePic.status == Image.Ready)profilePic.opacity = 1
            }

            Text {
                id: profileDetails
                x: 62
                y: 7
                color: "#73b8d3"
                text: "text"
                anchors.bottom: profilePic.top
                anchors.bottomMargin: 0
                font.pixelSize: 12
            }
        }
    }

    states: [
        State {
            name: "ss_searchpeople"

            PropertyChanges {
                target: searchPeopleItem
                opacity: 1
            }

            PropertyChanges {
                target: menuItem
                opacity: 0
            }

            PropertyChanges {
                target: strecher
                width: 274
                height: 100
            }

            PropertyChanges {
                target: homeImage
                opacity: 1
            }

            PropertyChanges {
                target: clickHome
                opacity: 1
            }
        },
        State {
            name: "ss_searchpeople_res"
            PropertyChanges {
                target: searchPeopleItem
                opacity: 1
            }

            PropertyChanges {
                target: menuItem
                opacity:0
            }

            PropertyChanges {
                target: strecher
                width: "274"
                height: "100"
            }

            PropertyChanges {
                target: homeImage
                opacity: 1
            }

            PropertyChanges {
                target: clickHome
                opacity: 1
            }

            PropertyChanges {
                target: bottom
                x: 0
                y: 150
            }
            PropertyChanges {
                target: middle502
                height: 50
            }

            PropertyChanges {
                target: base
                height: 200
            }

            PropertyChanges {
                target: searchResult
                width: 261
                height: 99
                opacity: 1
            }

        },
        State {
            name: "ss_login"

            PropertyChanges {
                target: menuItem
                opacity: 0
            }

            PropertyChanges {
                target: loginItem
                y: 37
                opacity: 1
            }

            PropertyChanges {
                target: text1
                opacity: 1
            }

            PropertyChanges {
                target: text2
                x: 9
                y: 48
                opacity: 1
            }

            PropertyChanges {
                target: homeImage
                opacity: 1
            }

            PropertyChanges {
                target: clickHome
                opacity: 1
            }

            PropertyChanges {
                target: middle502
                height: 25
            }
            PropertyChanges {
                target: bottom
                y: 125
            }

            PropertyChanges {
                target: loginButton
                x: 184
                y: 73
                anchors.rightMargin: 0
            }

            PropertyChanges {
                target: loginButtonClick
                opacity: 1
            }

            PropertyChanges {
                target: base
                height: 175
            }
        }
    ]
}
