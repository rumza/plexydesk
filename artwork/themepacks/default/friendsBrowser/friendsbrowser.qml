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
import PlexyDesk.Facebook.FriendListModel 1.0
import "resources/"
import "../resources/components/"

Rectangle {
   id: root
   width: 440
   height: 320
   color:  "transparent"
   SvgBackground
   {
      height: parent.height
      width: parent.width
   }

   ListView {
      id: friendsList
      x: 10
      y: 10
      width: parent.width -20
      height: parent.height-40
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      cacheBuffer: 1000
      clip: true
      delegate: friendDelegate
      model:friendmodel
      Component
      {
         id:friendDelegate
         Rectangle{
            id: friendBorder
            width: friendsList.width-20
            height: 60
            color:"transparent"

            Rectangle
            {
               id: friend
               color:"white"
               radius: 4
               opacity: 0.5
               width: parent.width - 4;
               height: parent.height - 4;
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.verticalCenter: parent.verticalCenter
            }
            Friend
            {
               x: friend.x+3
               y: friend.y+3
               fbId: facebookId
               fbName: facebookName
               thumbSrc: profilePicture

            }
            MouseArea
            {
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: {friend.color= "lightblue";friend.opacity = 1;}
                onExited: {friend.color= "white";friend.opacity = 0.5;}
                onClicked: friendmodel.friendSelected(facebookId)
            }
         }
      }
   }
   FriendListModel
   {
      id: friendmodel
   }
}

