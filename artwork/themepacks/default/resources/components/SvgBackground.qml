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

   Rectangle
   {
      color:"transparent"
      Image {
              id: background
              sourceSize.width: parent.width - 20
              sourceSize.height: parent.height - 20
              source: "image://plexydesk_svgprovider/background_-center"
              x : 10
              y : 10
              z: -100
              asynchronous : true
              opacity: 0.35
              smooth: true
          }

          Image {
              id: background_center
              sourceSize.width: parent.width - 20
              sourceSize.height: parent.height - 20
              source: "image://plexydesk_svgprovider/background_-center"
              x : 10
              y : 10
              z: -100
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_topleft
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : 10
              source: "image://plexydesk_svgprovider/background_-topleft"
              x: 0
              y: 0
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_topright
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : 10
              source: "image://plexydesk_svgprovider/background_-topright"
              x: parent.width - 10
              y: 0
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_top
              sourceSize.width: 10
              sourceSize.height: 10
              width : parent.width - 20
              height : 10
              source: "image://plexydesk_svgprovider/background_-top"
              x: 10
              y: 0
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_right
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : parent.height - 20
              source: "image://plexydesk_svgprovider/background_-right"
              x: parent.width - 10
              y: 10
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_bottomright
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : 10
              source: "image://plexydesk_svgprovider/background_-bottomright"
              x: parent.width - 10
              y: parent.height - 10
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_bottom
              sourceSize.width: 10
              sourceSize.height: 10
              width : parent.width - 20
              height : 10
              source: "image://plexydesk_svgprovider/background_-bottom"
              x: 10
              y: parent.height - 10
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_bottomleft
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : 10
              source: "image://plexydesk_svgprovider/background_-bottomleft"
              x: 0
              y: parent.height - 10
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_left
              sourceSize.width: 10
              sourceSize.height: 10
              width : 10
              height : parent.height - 20
              source: "image://plexydesk_svgprovider/background_-left"
              x: 0
              y: 10
              z: -101
              asynchronous : true
              opacity: 1
              smooth: true
          }

          Image {
              id: background_content
              source: "image://plexydesk_svgprovider/background_-center"
              anchors.top: background.top
              anchors.left: background.left
              z: -90
              width: parent.width - 20
              height: parent.height - 20
              sourceSize.width: 400
              sourceSize.height : 400
              opacity: 0.8
              asynchronous : true
              smooth: true
          }
          Image {
              id: close
              width: 16
              height: 16
              anchors.top: parent.top
              anchors.topMargin: 10
              anchors.right: parent.right
              anchors.rightMargin: 10
              source: "image://plexydesk_svgprovider/close"
              MouseArea
              {
                 anchors.fill: parent
                 onClicked: Qt.quit();
              }
          }
   }

