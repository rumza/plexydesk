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
   id:friend
   property alias contentType: hiddenContentType.text
   property alias fbId: userId.text
   property alias thumbSrc: thumb.source
   property alias fbName: name.text
   color: "transparent"
   radius: 10

   Text {
      id: hiddenContentType
      visible: false
   }
   Text {
      id: userId
      visible: false;
   }
   Image {
      id: thumb
      sourceSize.width: 60
      sourceSize.height: 60
      asynchronous: true
   }
   Text {
      id: name
      color:  "white"
      anchors.left: thumb.right
      anchors.leftMargin: 10
      anchors.horizontalCenter: thumb.horizontalCenter
   }
}
