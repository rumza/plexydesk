import Qt 4.7
import "../resources/components"
import PlexyDesk.Facebook.FriendListModel 1.0

Rectangle {
   id: root
   width: 440
   height: 220
   color: "transparent"

   SvgBackground
   {
      height: parent.height
      width: parent.width
   }

   Text {
      id: friendName
      text: friendsModel.contactName();
      color: "white"
      x:10
      y:170
   }
   Rectangle{
      id:silverBorder
      color: "silver"
      visible: false
      opacity: 0
      height: childrenRect.height+4
      width: childrenRect.width+4
      x:10
      y:10
      Image
      {
         id: picture
         y:2
         x:2
         opacity: 0;
         height: 150;
         fillMode: Image.PreserveAspectFit
         anchors.verticalCenter: root.verticalCenter
         source: friendsModel.contactPicture();
         onStatusChanged: {if(picture.status == Image.Ready)picture.opacity = 1;silverBorder.opacity  =1;silverBorder.visible = true;}
         Behavior on opacity {
            NumberAnimation{duration: 1000}
         }
      }
      Behavior on opacity {
         NumberAnimation{duration: 1000}
      }
   }

   Rectangle
   {
      id:controllers
      color: "transparent"
      anchors.left: parent.left
      anchors.top: parent.top
      anchors.bottom: parent.bottom
      width: 200

   }

   FriendListModel
   {
      id: friendsModel
   }




}
